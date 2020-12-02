import csv

import spotipy
import urllib3

import keys
import pprint
import queue
from itertools import combinations
from spotipy.oauth2 import SpotifyClientCredentials

pp = pprint.PrettyPrinter(indent=4)
auth_manager = SpotifyClientCredentials(keys.CLIENT_ID,
                                        keys.CLIENT_SECRET, requests_timeout=10)  # is in the .gitignore, ask kevin for details or take the cpp ones its the same
sp = spotipy.Spotify(auth_manager=auth_manager)


def findAlbumsFromArtist(artist_uri):
    albums = []
    response_single = sp.artist_albums(artist_uri, album_type='single')
    response_album = sp.artist_albums(artist_uri, album_type='album')
    while response_single:
        for i, album in enumerate(response_single['items']):
            if len(album['artists']) > 1:
                uri_album = (album['uri'], album['name'])
                albums.append(uri_album)
        if response_single['next']:
            response_single = sp.next(response_single)
        else:
            response_single = None

    while response_album:
        for i, album in enumerate(response_album['items']):
            if len(album['artists']) > 1:
                uri_album = (album['uri'], album['name'])
                albums.append(uri_album)
        if response_album['next']:
            response_album = sp.next(response_album)
        else:
            response_album = None
    return albums


def getAlbumTracks(album_uri):
    collab_artists = {}  # a set of tuples containing all the artists that this artist has worked with
    try:
        response = sp.album_tracks(album_uri)
        while response:
            for i, song in enumerate(response['items']):
                if len(song['artists']) > 1:
                    for j, artist in enumerate(song['artists']):
                        songname = (song['id'], song['name'], song['duration_ms'])
                        if songname in collab_artists:
                            collab_artists[songname].extend([(artist['id'], artist['name'])])
                        else:
                            collab_artists[songname] = [(artist['id'], artist['name'])]

            if response['next']:
                response = sp.next(response)
            else:
                response = None
        return collab_artists #Somethings weird with the request it'll stop sometimes
    except urllib3.exceptions.ReadTimeOutError:
        return collab_artists



def getAllData(seed_artist_uri):
    data = []
    artist_queue = queue.Queue()
    artist_queue.put(seed_artist_uri[15:])
    i = 0
    artist_set = set()
    while (not artist_queue.empty()) and i < 100:
        print(i)
        artist_uri = artist_queue.get()
        connected_artist_set = set()
        artist_set.add(artist_uri)
        print('spotify:artist:' + artist_uri)
        albums = findAlbumsFromArtist('spotify:artist:' + artist_uri)
        collab_albums = [uri[0] for uri in albums]
        for album_uri in collab_albums:

            collab_songs = getAlbumTracks(album_uri)

            for s in collab_songs:
                songartists = collab_songs[s]
                # pp.pprint(collab_songs) #printing all the songs
                comb = combinations(songartists, 2)  # get combinations of the artists that worked on this collab_song
                for c in list(comb):
                    # process entry into a list thats [id1, artist1, id2, artist2, id_song, songname, duration of song in ms]
                    entry = []
                    for com in c:
                        # adds the two artists id and names together to become one list
                        entry.extend(list(com))
                    # adds the song id and name to the list
                    entry.extend(list(s))
                    data.append(entry)

                uris = [uri[0] for uri in songartists]
                for uri in uris:
                    if (uri not in artist_set) and (uri not in connected_artist_set):
                        connected_artist_set.add(uri)
                        # print("inserting: ")
                        # print(sp.artist(uri)["name"])
                        artist_queue.put(uri)

        i += 1
    return data


jacob_collier_uri = 'spotify:artist:0QWrMNukfcVOmgEU0FEDyD'
all_data = getAllData(jacob_collier_uri)

pp.pprint(all_data)
fields = ["Id1", "Name1", "Id2", "Name2", "IdSong", "NameSong", "SongLengthMS"]
with open('artist_connections.csv', 'w', encoding='utf8') as f:
    # using csv.writer method from CSV package
    write = csv.writer(f, delimiter=',', lineterminator='\n')

    write.writerow(fields)
    for data_row in all_data:
        write.writerow(data_row)

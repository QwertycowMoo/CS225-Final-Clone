import spotipy
import keys
import pprint
import queue
from spotipy.oauth2 import SpotifyClientCredentials

pp = pprint.PrettyPrinter(indent=4)
auth_manager = SpotifyClientCredentials(keys.CLIENT_ID, keys.CLIENT_SECRET) #is in the .gitignore, ask kevin for details or take the cpp ones its the same
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
    response = sp.album_tracks(album_uri)
    collab_artists = {} # a set of tuples containing all the artists that this artist has worked with
    while response:
        for i, song in enumerate(response['items']):
            if len(song['artists']) > 1:
                for j, artist in enumerate(song['artists']):
                    songname = song['name']
                    if songname in collab_artists:
                        collab_artists[songname].extend([(artist['id'],artist['name'])])
                    else:
                        collab_artists[songname] = [(artist['id'], artist['name'])]

        if response['next']:
            response = sp.next(response)
        else:
            response = None
    return collab_artists


def getAllData(seed_artist_uri):

    artist_queue = queue.Queue()
    artist_queue.put(seed_artist_uri[15:])
    i = 0
    while (not artist_queue.empty()) or i > 20:
        artist_uri = artist_queue.get()
        artist_set = {artist_uri}
        print('spotify:artist:' + artist_uri)
        albums = findAlbumsFromArtist('spotify:artist:' + artist_uri)
        collab_albums = [uri[0] for uri in albums]
        for album_uri in collab_albums:
            collab_songs = getAlbumTracks(album_uri)
            pp.pprint(collab_songs)
            for s in collab_songs:
                #the problem is there will be a time where we have already visited the artist and then we'll do a loopback and basically do Jacob again
                #if we just use like a disjoint set, then it'll look like a spider and there wont be as many interconnections between artists
                #but idk how to get the other artists without backing up and redoing
                #maybe instead we use a disjoint set of songs?
                songartists = collab_songs[s]
                uris = [uri[0] for uri in songartists]
                for uri in uris:
                    artist_queue.put(uri)

        i += 1


jacob_collier_uri = 'spotify:artist:0QWrMNukfcVOmgEU0FEDyD'
getAllData(jacob_collier_uri)





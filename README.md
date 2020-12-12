# erf3-caleqw2-kjzhou2-evanmm3
Final Project

This project aims to create a graphical representation of artists on Spotify.
The Vertices of the graph are Artists and the Edges represent songs that two Artists have collaborated on together.

Presentation video [here](https://youtu.be/3ReWfrxZdWA).

# Creating your own CSV:
The CSV is ordered in this order:
`ArtistId1,ArtistName1,ArtistId2,ArtistName2,SongId,SongName,SongLengthInMilliSeconds`
## To create your own CSV using the python script:
The python file in SpotifyPython/SpotifyAPI is only a script. It requires the following packages to be installed in your local `venv`:  
`pip3 install spotipy`  
`pip3 install urllib3`  
And the script has a line 112 `seed_artist_uri` that is currently set to Jacob Collier's Spotify URI.   
    * To find this URI, go into a Spotify application and find the artist that you want to seed. Click "Share" and "Copy Spotify URI"  
    * Paste this URI into the value for the seed_artist_uri  
    * The Script will then find the 500 closest artist to the seed artist  

# Using the program
This program runs through the command line.
The executable name is `./spotigraph`. Make sure to cd into `\graphArtists`, run `make`, and determine your csv file path before you run any of the following commands.

## To print a list of all artists in a csv file:
`./spotigraph file.csv -a`
Ex:
`./spotigraph artist_connections.csv -a`

## To print a BFS traversal of all artists in a csv file:
`./spotigraph "Root Artist Name" file.csv -path=bfs`  
Ex:
`./spotigraph "Ariana Grande" artist_connections.csv -path=bfs`  

## To find a path between two artists using Dijkstra's Algorithm:
`./spotigraph "Source Artist Name" "Destination Artist Name" file.csv -path=dijk`  
Ex:
`./spotigraph "Ariana Grande" "Jon Bellion" artist_connections.csv -path=dijk`  

## To find a path between two artists with a landmark artist in between
`./spotigraph "Source Artist Name" "Landmark Artist Name "Destination Artist Name" file.csv -path=landmark`  
Ex:
`./spotigraph "Jacob Collier" "Ariana Grande" "Yung Gravy" artist_connections.csv -path=landmark`  

# Next Steps:
Have a python script or node.js program that allows you to login to spotify and create a playlist using these songs.

## Things we learned:
- cURL in C++ is complicated. Python is better.
- Implementation of BFS, Dijkstra's, and Landmark Path
- Use of multiple data structures in tandem and how they interact in C++
- Use of Github and project management
- Pair programming is an incredibly efficient way to write better code and catch bugs along the way.

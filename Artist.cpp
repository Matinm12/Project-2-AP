#include "Artist.h"
#include <iostream>
#include <algorithm>

Artist::Artist(const std::string& name) : name(name) {}

void Artist::addSong(const Song& song) {
    if (std::find(songs.begin(), songs.end(), song) == songs.end()) {
        songs.push_back(song);
    }
}

void Artist::addAlbum(const Playlist& album) {
    albums.push_back(album);
}

void Artist::displayProfile() const {
    std::cout << "\n=== Artist Profile ==="
              << "\nName: " << name
              << "\nSongs: " << songs.size()
              << "\nAlbums: " << albums.size() << "\n";

    std::cout << "\nTop Songs:";
    for (size_t i = 0; i < std::min(songs.size(), size_t(5)); ++i) {
        std::cout << "\n- " << songs[i].getTitle();
    }

    std::cout << "\n\nAlbums:";
    for (const auto& album : albums) {
        std::cout << "\n- " << album.getName();
    }
    std::cout << "\n";
}

std::string Artist::getName() const { return name; }
const std::vector<Song>& Artist::getSongs() const { return songs; }
const std::vector<Playlist>& Artist::getAlbums() const { return albums; }
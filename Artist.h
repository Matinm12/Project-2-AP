#ifndef ARTIST_H
#define ARTIST_H
#include "Song.h"
#include "Playlist.h"
#include <vector>
#include <string>

class Artist {
private:
    std::string name;
    std::vector<Song> songs;
    std::vector<Playlist> albums;

public:
    Artist(const std::string& name = "");

    void addSong(const Song& song);
    void addAlbum(const Playlist& album);
    void displayProfile() const;

    std::string getName() const;
    const std::vector<Song>& getSongs() const;
    const std::vector<Playlist>& getAlbums() const;
};
#endif
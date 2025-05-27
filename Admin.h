#ifndef ADMIN_H
#define ADMIN_H
#include "Song.h"
#include "Artist.h"
#include "Playlist.h"
#include <vector>
#include <string>

class Admin {
private:
    const std::string ADMIN_USERNAME = "admin";
    const std::string ADMIN_PASSWORD = "admin123";
    std::vector<Song> allSongs;
    std::vector<Artist> artists;
    std::vector<Playlist> systemPlaylists;

public:
    bool authenticate(const std::string& uname, const std::string& pwd) const;
    void addSong(const Song& song);
    bool removeSong(const std::string& title);
    void createArtist(const std::string& name);
    void createSystemPlaylist(const std::string& name);
    bool addSongToSystemPlaylist(const std::string& playlistName, const Song& song);
    void displayAllData() const;

    const std::vector<Song>& getAllSongs() const;
    const std::vector<Artist>& getArtists() const;
    const std::vector<Playlist>& getSystemPlaylists() const;
};
#endif
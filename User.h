#ifndef USER_H
#define USER_H
#include "Song.h"
#include "Playlist.h"
#include <vector>
#include <string>
#include <algorithm>

class User {
private:
    std::string username;
    std::string password;
    std::vector<Song> favoriteSongs;
    std::vector<Playlist> personalPlaylists;

public:
    User(const std::string& username = "", const std::string& password = "");

    bool authenticate(const std::string& uname, const std::string& pwd) const;
    void addFavoriteSong(const Song& song);
    bool removeFavoriteSong(const std::string& title);
    void createPlaylist(const std::string& name);
    bool deletePlaylist(const std::string& name);
    bool addSongToPlaylist(const std::string& playlistName, const Song& song);
    bool removeSongFromPlaylist(const std::string& playlistName, const std::string& songTitle);
    Playlist* getPlaylist(const std::string& name);
    void displayDashboard() const;

    std::string getUsername() const;
    const std::vector<Song>& getFavoriteSongs() const;
    const std::vector<Playlist>& getPersonalPlaylists() const;
};
#endif
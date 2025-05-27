#include "User.h"
#include <iostream>

User::User(const std::string& username, const std::string& password)
        : username(username), password(password) {}

bool User::authenticate(const std::string& uname, const std::string& pwd) const {
    return uname == username && pwd == password;
}

void User::addFavoriteSong(const Song& song) {
    if (std::find(favoriteSongs.begin(), favoriteSongs.end(), song) == favoriteSongs.end()) {
        favoriteSongs.push_back(song);
    }
}

bool User::removeFavoriteSong(const std::string& title) {
    auto it = std::find_if(favoriteSongs.begin(), favoriteSongs.end(),
                           [&title](const Song& s) { return s.getTitle() == title; });

    if (it != favoriteSongs.end()) {
        favoriteSongs.erase(it);
        return true;
    }
    return false;
}

void User::createPlaylist(const std::string& name) {
    personalPlaylists.emplace_back(name);
}

bool User::deletePlaylist(const std::string& name) {
    auto it = std::find_if(personalPlaylists.begin(), personalPlaylists.end(),
                           [&name](const Playlist& p) { return p.getName() == name; });

    if (it != personalPlaylists.end()) {
        personalPlaylists.erase(it);
        return true;
    }
    return false;
}

bool User::addSongToPlaylist(const std::string& playlistName, const Song& song) {
    for (auto& playlist : personalPlaylists) {
        if (playlist.getName() == playlistName) {
            playlist.addSong(song);
            return true;
        }
    }
    return false;
}

bool User::removeSongFromPlaylist(const std::string& playlistName, const std::string& songTitle) {
    for (auto& playlist : personalPlaylists) {
        if (playlist.getName() == playlistName) {
            return playlist.removeSong(songTitle);
        }
    }
    return false;
}

Playlist* User::getPlaylist(const std::string& name) {
    auto it = std::find_if(personalPlaylists.begin(), personalPlaylists.end(),
                           [&name](const Playlist& p) { return p.getName() == name; });
    return it != personalPlaylists.end() ? &(*it) : nullptr;
}

void User::displayDashboard() const {
    std::cout << "\n=== User Dashboard ==="
              << "\nUsername: " << username
              << "\nFavorite Songs: " << favoriteSongs.size()
              << "\nPlaylists: " << personalPlaylists.size() << "\n";
}

std::string User::getUsername() const { return username; }
const std::vector<Song>& User::getFavoriteSongs() const { return favoriteSongs; }
const std::vector<Playlist>& User::getPersonalPlaylists() const { return personalPlaylists; }
#include "Admin.h"
#include <algorithm>
#include <iostream>

bool Admin::authenticate(const std::string& uname, const std::string& pwd) const {
    return uname == ADMIN_USERNAME && pwd == ADMIN_PASSWORD;
}

void Admin::addSong(const Song& song) {
    if (std::find(allSongs.begin(), allSongs.end(), song) == allSongs.end()) {
        allSongs.push_back(song);

        // Add to artist
        auto it = std::find_if(artists.begin(), artists.end(),
                               [&song](const Artist& a) { return a.getName() == song.getArtist(); });

        if (it != artists.end()) {
            const_cast<Artist&>(*it).addSong(song);
        } else {
            Artist newArtist(song.getArtist());
            newArtist.addSong(song);
            artists.push_back(newArtist);
        }
    }
}

bool Admin::removeSong(const std::string& title) {
    auto it = std::find_if(allSongs.begin(), allSongs.end(),
                           [&title](const Song& s) { return s.getTitle() == title; });

    if (it != allSongs.end()) {
        // Remove from artists
        for (auto& artist : artists) {
            const_cast<Artist&>(artist).addSong(*it); // Temporary fix
        }

        // Remove from playlists
        for (auto& playlist : systemPlaylists) {
            const_cast<Playlist&>(playlist).removeSong(title);
        }

        allSongs.erase(it);
        return true;
    }
    return false;
}

void Admin::createArtist(const std::string& name) {
    if (std::find_if(artists.begin(), artists.end(),
                     [&name](const Artist& a) { return a.getName() == name; }) == artists.end()) {
        artists.emplace_back(name);
    }
}

void Admin::createSystemPlaylist(const std::string& name) {
    systemPlaylists.emplace_back(name);
}

bool Admin::addSongToSystemPlaylist(const std::string& playlistName, const Song& song) {
    for (auto& playlist : systemPlaylists) {
        if (playlist.getName() == playlistName) {
            playlist.addSong(song);
            return true;
        }
    }
    return false;
}

void Admin::displayAllData() const {
    std::cout << "\n=== System Data ==="
              << "\nTotal Songs: " << allSongs.size()
              << "\nTotal Artists: " << artists.size()
              << "\nTotal Playlists: " << systemPlaylists.size() << "\n";
}

const std::vector<Song>& Admin::getAllSongs() const { return allSongs; }
const std::vector<Artist>& Admin::getArtists() const { return artists; }
const std::vector<Playlist>& Admin::getSystemPlaylists() const { return systemPlaylists; }
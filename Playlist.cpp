#include "Playlist.h"
#include <iostream>
#include <algorithm>

Playlist::Playlist(const std::string& name)
        : name(name), currentSongIndex(0), isLooping(false),
          playMode(SEQUENTIAL) {
    std::srand(std::time(0));
}

void Playlist::addSong(const Song& song) {
    if (std::find(songs.begin(), songs.end(), song) == songs.end()) {
        songs.push_back(song);
    }
}

bool Playlist::removeSong(const std::string& title) {
    auto it = std::find_if(songs.begin(), songs.end(),
                           [&title](const Song& s) { return s.getTitle() == title; });

    if (it != songs.end()) {
        songs.erase(it);
        if (currentSongIndex >= songs.size()) {
            currentSongIndex = std::max(0, (int)songs.size() - 1);
        }
        return true;
    }
    return false;
}

void Playlist::clear() {
    songs.clear();
    currentSongIndex = 0;
}

Song* Playlist::getCurrentSong() {
    if (songs.empty()) return nullptr;
    return &songs[currentSongIndex];
}

Song* Playlist::nextSong() {
    if (songs.empty()) return nullptr;

    switch (playMode) {
        case SEQUENTIAL:
            currentSongIndex = (currentSongIndex + 1) % songs.size();
            break;
        case RANDOM:
            currentSongIndex = rand() % songs.size();
            break;
        case REPEAT_ONE:
            break;
    }
    return getCurrentSong();
}

Song* Playlist::previousSong() {
    if (songs.empty()) return nullptr;
    currentSongIndex = (currentSongIndex - 1 + songs.size()) % songs.size();
    return getCurrentSong();
}

void Playlist::setPlayMode(PlayMode mode) { playMode = mode; }
void Playlist::toggleLoop() { isLooping = !isLooping; }

void Playlist::display(bool showSongs) const {
    std::cout << "\nPlaylist: " << name << " (" << songs.size() << " songs)";
    if (showSongs) {
        for (size_t i = 0; i < songs.size(); ++i) {
            std::cout << "\n" << i+1 << ". " << songs[i].getTitle();
        }
    }
    std::cout << "\n";
}

void Playlist::displayCurrent() const {
    if (!songs.empty()) {
        std::cout << "\nNow Playing: " << songs[currentSongIndex].getTitle() << "\n";
    }
}

std::string Playlist::getName() const { return name; }
size_t Playlist::getSongCount() const { return songs.size(); }
const std::vector<Song>& Playlist::getSongs() const { return songs; }
bool Playlist::isEmpty() const { return songs.empty(); }
Playlist::PlayMode Playlist::getPlayMode() const { return playMode; }
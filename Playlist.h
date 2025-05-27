#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "Song.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Playlist {
public:
    enum PlayMode { SEQUENTIAL, RANDOM, REPEAT_ONE };

private:
    std::string name;
    std::vector<Song> songs;
    int currentSongIndex;
    bool isLooping;
    PlayMode playMode;

public:
    Playlist(const std::string& name = "");


    void addSong(const Song& song);
    bool removeSong(const std::string& title);
    void clear();


    Song* getCurrentSong();
    Song* nextSong();
    Song* previousSong();


    void setPlayMode(PlayMode mode);
    void toggleLoop();


    void display(bool showSongs = true) const;
    void displayCurrent() const;


    std::string getName() const;
    size_t getSongCount() const;
    const std::vector<Song>& getSongs() const;
    bool isEmpty() const;
    PlayMode getPlayMode() const;
};
#endif
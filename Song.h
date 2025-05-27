#ifndef SONG_H
#define SONG_H
#include <string>
#include <algorithm>

class Song {
private:
    std::string title;
    std::string artist;
    int releaseYear;
    std::string genre;

public:
    Song(const std::string& title = "", const std::string& artist = "",
         int year = 0, const std::string& genre = "");


    void displayInfo() const;


    bool matches(const std::string& query) const;


    std::string getTitle() const;
    std::string getArtist() const;
    int getReleaseYear() const;
    std::string getGenre() const;

    bool operator==(const Song& other) const;
};
#endif
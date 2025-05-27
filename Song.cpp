#include "Song.h"
#include <iostream>

Song::Song(const std::string& title, const std::string& artist,
           int year, const std::string& genre)
        : title(title), artist(artist), releaseYear(year), genre(genre) {}

void Song::displayInfo() const {
    std::cout << "\nTitle: " << title
              << "\nArtist: " << artist
              << "\nYear: " << releaseYear
              << "\nGenre: " << genre << "\n";
}

bool Song::matches(const std::string& query) const {
    std::string q = query;
    std::transform(q.begin(), q.end(), q.begin(), ::tolower);

    std::string t = title;
    std::transform(t.begin(), t.end(), t.begin(), ::tolower);

    return t.find(q) != std::string::npos ||
           artist.find(q) != std::string::npos ||
           genre.find(q) != std::string::npos;
}

std::string Song::getTitle() const { return title; }
std::string Song::getArtist() const { return artist; }
int Song::getReleaseYear() const { return releaseYear; }
std::string Song::getGenre() const { return genre; }

bool Song::operator==(const Song& other) const {
    return title == other.title && artist == other.artist;
}
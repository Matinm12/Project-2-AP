#include "MusicPlayerSystem.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

MusicPlayerSystem::MusicPlayerSystem()
        : currentUser(nullptr), isAdminLoggedIn(false) {
    std::srand(std::time(0));
    initializeSampleData();
}

void MusicPlayerSystem::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void MusicPlayerSystem::initializeSampleData() {
    // Sample songs
    admin.addSong(Song("Bohemian Rhapsody", "Queen", 1975, "Rock"));
    admin.addSong(Song("Imagine", "John Lennon", 1971, "Pop"));
    admin.addSong(Song("Hotel California", "Eagles", 1976, "Rock"));
    admin.addSong(Song("Sweet Child O'Mine", "Guns N' Roses", 1987, "Rock"));
    admin.addSong(Song("Billie Jean", "Michael Jackson", 1982, "Pop"));

    // Sample artists
    admin.createArtist("Queen");
    admin.createArtist("John Lennon");
    admin.createArtist("Eagles");

    // Sample playlists
    admin.createSystemPlaylist("Classic Rock");
    admin.addSongToSystemPlaylist("Classic Rock", admin.getAllSongs()[0]);
    admin.addSongToSystemPlaylist("Classic Rock", admin.getAllSongs()[2]);
}

void MusicPlayerSystem::run() {
#ifdef _WIN32
    SetConsoleOutputCP(65001); // Enable UTF-8 in Windows
#endif

    while (true) {
        clearScreen();
        displayMainMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: userLogin(); break;
            case 2: userRegister(); break;
            case 3: adminLogin(); break;
            case 4: return;
            default:
                std::cout << "Invalid choice. Try again.\n";
                std::cin.get();
        }
    }
}

void MusicPlayerSystem::displayMainMenu() {
    std::cout << "\n=== Music Player ==="
              << "\n1. User Login"
              << "\n2. User Register"
              << "\n3. Admin Login"
              << "\n4. Exit"
              << "\nEnter choice: ";
}

void MusicPlayerSystem::userLogin() {
    clearScreen();
    std::string username, password;
    std::cout << "=== User Login ===\n";
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    for (auto& user : users) {
        if (user.authenticate(username, password)) {
            currentUser = &user;
            isAdminLoggedIn = false;
            userDashboard();
            return;
        }
    }
    std::cout << "Login failed.\n";
    std::cin.get();
}

void MusicPlayerSystem::userRegister() {
    clearScreen();
    std::string username, password;
    std::cout << "=== User Registration ===\n";
    std::cout << "Choose username: ";
    std::getline(std::cin, username);
    std::cout << "Choose password: ";
    std::getline(std::cin, password);

    // Check if username exists
    if (std::find_if(users.begin(), users.end(),
                     [&username](const User& u) { return u.getUsername() == username; }) != users.end()) {
        std::cout << "Username already exists.\n";
        std::cin.get();
        return;
    }

    users.emplace_back(username, password);
    std::cout << "Registration successful. You can now login.\n";
    std::cin.get();
}

void MusicPlayerSystem::adminLogin() {
    clearScreen();
    std::string username, password;
    std::cout << "=== Admin Login ===\n";
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    if (admin.authenticate(username, password)) {
        isAdminLoggedIn = true;
        adminPanel();
    } else {
        std::cout << "Admin login failed.\n";
        std::cin.get();
    }
}

void MusicPlayerSystem::userDashboard() {
    while (currentUser) {
        clearScreen();
        std::cout << "\n=== User Dashboard (" << currentUser->getUsername() << ") ==="
                  << "\n1. Play Songs"
                  << "\n2. Manage Playlists"
                  << "\n3. Manage Favorites"
                  << "\n4. Search Songs"
                  << "\n5. View Artists"
                  << "\n6. View Dashboard"
                  << "\n7. Logout"
                  << "\nEnter choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: playSongs(); break;
            case 2: managePlaylists(); break;
            case 3: manageFavorites(); break;
            case 4: searchSongs(); break;
            case 5: showArtists(); break;
            case 6: {
                clearScreen();
                currentUser->displayDashboard();
                std::cout << "\nPress enter to continue...";
                std::cin.get();
                break;
            }
            case 7:
                currentUser = nullptr;
                return;
            default:
                std::cout << "Invalid choice.\n";
                std::cin.get();
        }
    }
}

void MusicPlayerSystem::adminPanel() {
    while (isAdminLoggedIn) {
        clearScreen();
        std::cout << "\n=== Admin Panel ==="
                  << "\n1. View All Data"
                  << "\n2. Add Song"
                  << "\n3. Add Artist"
                  << "\n4. Add Playlist"
                  << "\n5. Logout"
                  << "\nEnter choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                clearScreen();
                admin.displayAllData();
                std::cout << "\nPress enter to continue...";
                std::cin.get();
                break;
            }
            case 2: {
                clearScreen();
                std::string title, artist, genre;
                int year;

                std::cout << "=== Add New Song ===\n";
                std::cout << "Title: ";
                std::getline(std::cin, title);
                std::cout << "Artist: ";
                std::getline(std::cin, artist);
                std::cout << "Year: ";
                std::cin >> year;
                std::cin.ignore();
                std::cout << "Genre: ";
                std::getline(std::cin, genre);

                admin.addSong(Song(title, artist, year, genre));
                std::cout << "Song added successfully.\n";
                std::cin.get();
                break;
            }
            case 3: {
                clearScreen();
                std::string name;
                std::cout << "=== Add New Artist ===\n";
                std::cout << "Artist name: ";
                std::getline(std::cin, name);
                admin.createArtist(name);
                std::cout << "Artist added successfully.\n";
                std::cin.get();
                break;
            }
            case 4: {
                clearScreen();
                std::string name;
                std::cout << "=== Create New Playlist ===\n";
                std::cout << "Playlist name: ";
                std::getline(std::cin, name);
                admin.createSystemPlaylist(name);
                std::cout << "Playlist created successfully.\n";
                std::cin.get();
                break;
            }
            case 5:
                isAdminLoggedIn = false;
                return;
            default:
                std::cout << "Invalid choice.\n";
                std::cin.get();
        }
    }
}

void MusicPlayerSystem::playSongs() {
    const auto& allSongs = admin.getAllSongs();
    if (allSongs.empty()) {
        clearScreen();
        std::cout << "No songs available.\n";
        std::cin.get();
        return;
    }

    std::vector<Song*> songsPtr;
    for (auto& song : const_cast<std::vector<Song>&>(allSongs)) {
        songsPtr.push_back(&song);
    }

    int currentIndex = 0;
    while (true) {
        clearScreen();
        std::cout << "=== Now Playing ===\n";
        songsPtr[currentIndex]->displayInfo();

        std::cout << "\nOptions:\n"
                  << "1. Next Song\n"
                  << "2. Previous Song\n"
                  << "3. Add to Favorites\n"
                  << "4. Add to Playlist\n"
                  << "5. Back\n"
                  << "Choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            currentIndex = (currentIndex + 1) % songsPtr.size();
        }
        else if (choice == 2) {
            currentIndex = (currentIndex - 1 + songsPtr.size()) % songsPtr.size();
        }
        else if (choice == 3) {
            currentUser->addFavoriteSong(*songsPtr[currentIndex]);
            std::cout << "Added to favorites!\n";
            std::cin.get();
        }
        else if (choice == 4) {
            const auto& playlists = currentUser->getPersonalPlaylists();
            if (playlists.empty()) {
                std::cout << "You have no playlists. Create one first.\n";
            } else {
                std::cout << "Your Playlists:\n";
                for (size_t i = 0; i < playlists.size(); ++i) {
                    std::cout << i+1 << ". " << playlists[i].getName() << "\n";
                }

                std::cout << "Select playlist (number): ";
                size_t playlistChoice;
                std::cin >> playlistChoice;
                std::cin.ignore();

                if (playlistChoice > 0 && playlistChoice <= playlists.size()) {
                    if (currentUser->addSongToPlaylist(playlists[playlistChoice-1].getName(),
                                                       *songsPtr[currentIndex])) {
                        std::cout << "Song added to playlist!\n";
                    } else {
                        std::cout << "Failed to add song.\n";
                    }
                } else {
                    std::cout << "Invalid choice.\n";
                }
            }
            std::cin.get();
        }
        else if (choice == 5) {
            return;
        }
        else {
            std::cout << "Invalid choice.\n";
            std::cin.get();
        }
    }
}

void MusicPlayerSystem::managePlaylists() {
    while (true) {
        clearScreen();
        std::cout << "\n=== Manage Playlists ==="
                  << "\n1. Create New Playlist"
                  << "\n2. View My Playlists"
                  << "\n3. Add Song to Playlist"
                  << "\n4. Remove Song from Playlist"
                  << "\n5. Back"
                  << "\nEnter choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            clearScreen();
            std::string name;
            std::cout << "Enter playlist name: ";
            std::getline(std::cin, name);
            currentUser->createPlaylist(name);
            std::cout << "Playlist created successfully.\n";
            std::cin.get();
        }
        else if (choice == 2) {
            clearScreen();
            const auto& playlists = currentUser->getPersonalPlaylists();
            if (playlists.empty()) {
                std::cout << "You have no playlists.\n";
            } else {
                std::cout << "Your Playlists:\n";
                for (const auto& playlist : playlists) {
                    playlist.display();
                }
            }
            std::cout << "\nPress enter to continue...";
            std::cin.get();
        }
        else if (choice == 3) {
            clearScreen();
            const auto& playlists = currentUser->getPersonalPlaylists();
            if (playlists.empty()) {
                std::cout << "You have no playlists. Create one first.\n";
                std::cin.get();
                continue;
            }

            std::cout << "Select playlist:\n";
            for (size_t i = 0; i < playlists.size(); ++i) {
                std::cout << i+1 << ". " << playlists[i].getName() << "\n";
            }

            std::cout << "Enter playlist number: ";
            size_t playlistNum;
            std::cin >> playlistNum;
            std::cin.ignore();

            if (playlistNum < 1 || playlistNum > playlists.size()) {
                std::cout << "Invalid playlist number.\n";
                std::cin.get();
                continue;
            }

            const auto& allSongs = admin.getAllSongs();
            if (allSongs.empty()) {
                std::cout << "No songs available.\n";
                std::cin.get();
                continue;
            }

            std::cout << "Available Songs:\n";
            for (size_t i = 0; i < allSongs.size(); ++i) {
                std::cout << i+1 << ". " << allSongs[i].getTitle() << "\n";
            }

            std::cout << "Enter song number to add: ";
            size_t songNum;
            std::cin >> songNum;
            std::cin.ignore();

            if (songNum < 1 || songNum > allSongs.size()) {
                std::cout << "Invalid song number.\n";
            } else {
                if (currentUser->addSongToPlaylist(playlists[playlistNum-1].getName(),
                                                   allSongs[songNum-1])) {
                    std::cout << "Song added to playlist successfully.\n";
                } else {
                    std::cout << "Song already exists in playlist.\n";
                }
            }
            std::cin.get();
        }
        else if (choice == 4) {
            clearScreen();
            const auto& playlists = currentUser->getPersonalPlaylists();
            if (playlists.empty()) {
                std::cout << "You have no playlists.\n";
                std::cin.get();
                continue;
            }

            std::cout << "Select playlist:\n";
            for (size_t i = 0; i < playlists.size(); ++i) {
                std::cout << i+1 << ". " << playlists[i].getName() << "\n";
            }

            std::cout << "Enter playlist number: ";
            size_t playlistNum;
            std::cin >> playlistNum;
            std::cin.ignore();

            if (playlistNum < 1 || playlistNum > playlists.size()) {
                std::cout << "Invalid playlist number.\n";
                std::cin.get();
                continue;
            }

            const auto& songs = playlists[playlistNum-1].getSongs();
            if (songs.empty()) {
                std::cout << "Playlist is empty.\n";
                std::cin.get();
                continue;
            }

            std::cout << "Songs in playlist:\n";
            for (size_t i = 0; i < songs.size(); ++i) {
                std::cout << i+1 << ". " << songs[i].getTitle() << "\n";
            }

            std::cout << "Enter song number to remove: ";
            size_t songNum;
            std::cin >> songNum;
            std::cin.ignore();

            if (songNum < 1 || songNum > songs.size()) {
                std::cout << "Invalid song number.\n";
            } else {
                if (currentUser->removeSongFromPlaylist(playlists[playlistNum-1].getName(),
                                                        songs[songNum-1].getTitle())) {
                    std::cout << "Song removed from playlist successfully.\n";
                } else {
                    std::cout << "Failed to remove song.\n";
                }
            }
            std::cin.get();
        }
        else if (choice == 5) {
            return;
        }
        else {
            std::cout << "Invalid choice.\n";
            std::cin.get();
        }
    }
}

void MusicPlayerSystem::manageFavorites() {
    while (true) {
        clearScreen();
        std::cout << "\n=== Manage Favorites ==="
                  << "\n1. View Favorite Songs"
                  << "\n2. Add Song to Favorites"
                  << "\n3. Remove Song from Favorites"
                  << "\n4. Back"
                  << "\nEnter choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            clearScreen();
            const auto& favorites = currentUser->getFavoriteSongs();
            if (favorites.empty()) {
                std::cout << "No favorite songs.\n";
            } else {
                std::cout << "Your Favorite Songs:\n";
                for (size_t i = 0; i < favorites.size(); ++i) {
                    std::cout << i+1 << ". " << favorites[i].getTitle() << "\n";
                }
            }
            std::cout << "\nPress enter to continue...";
            std::cin.get();
        }
        else if (choice == 2) {
            clearScreen();
            const auto& allSongs = admin.getAllSongs();
            if (allSongs.empty()) {
                std::cout << "No songs available.\n";
                std::cin.get();
                continue;
            }

            std::cout << "Available Songs:\n";
            for (size_t i = 0; i < allSongs.size(); ++i) {
                std::cout << i+1 << ". " << allSongs[i].getTitle() << "\n";
            }

            std::cout << "Enter song number to add: ";
            size_t songNum;
            std::cin >> songNum;
            std::cin.ignore();

            if (songNum < 1 || songNum > allSongs.size()) {
                std::cout << "Invalid song number.\n";
            } else {
                currentUser->addFavoriteSong(allSongs[songNum-1]);
                std::cout << "Song added to favorites successfully.\n";
            }
            std::cin.get();
        }
        else if (choice == 3) {
            clearScreen();
            const auto& favorites = currentUser->getFavoriteSongs();
            if (favorites.empty()) {
                std::cout << "No favorite songs to remove.\n";
                std::cin.get();
                continue;
            }

            std::cout << "Your Favorite Songs:\n";
            for (size_t i = 0; i < favorites.size(); ++i) {
                std::cout << i+1 << ". " << favorites[i].getTitle() << "\n";
            }

            std::cout << "Enter song number to remove: ";
            size_t songNum;
            std::cin >> songNum;
            std::cin.ignore();

            if (songNum < 1 || songNum > favorites.size()) {
                std::cout << "Invalid song number.\n";
            } else {
                if (currentUser->removeFavoriteSong(favorites[songNum-1].getTitle())) {
                    std::cout << "Song removed from favorites successfully.\n";
                } else {
                    std::cout << "Failed to remove song.\n";
                }
            }
            std::cin.get();
        }
        else if (choice == 4) {
            return;
        }
        else {
            std::cout << "Invalid choice.\n";
            std::cin.get();
        }
    }
}

void MusicPlayerSystem::searchSongs() {
    clearScreen();
    std::string query;
    std::cout << "=== Search Songs ===\n";
    std::cout << "Enter search term: ";
    std::getline(std::cin, query);

    std::vector<Song*> results;
    for (auto& song : const_cast<std::vector<Song>&>(admin.getAllSongs())) {
        if (song.matches(query)) {
            results.push_back(&song);
        }
    }

    if (results.empty()) {
        std::cout << "No songs found matching your search.\n";
        std::cin.get();
        return;
    }

    clearScreen();
    std::cout << "=== Search Results ===\n";
    displaySongs(results);

    std::cout << "\nEnter song number to view details (0 to go back): ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice > 0 && choice <= results.size()) {
        clearScreen();
        std::cout << "=== Song Details ===\n";
        results[choice-1]->displayInfo();

        std::cout << "\nOptions:\n"
                  << "1. Add to Favorites\n"
                  << "2. Add to Playlist\n"
                  << "3. Back\n"
                  << "Choice: ";

        int action;
        std::cin >> action;
        std::cin.ignore();

        if (action == 1) {
            currentUser->addFavoriteSong(*results[choice-1]);
            std::cout << "Added to favorites!\n";
            std::cin.get();
        }
        else if (action == 2) {
            const auto& playlists = currentUser->getPersonalPlaylists();
            if (playlists.empty()) {
                std::cout << "You have no playlists. Create one first.\n";
            } else {
                std::cout << "Your Playlists:\n";
                for (size_t i = 0; i < playlists.size(); ++i) {
                    std::cout << i+1 << ". " << playlists[i].getName() << "\n";
                }

                std::cout << "Select playlist (number): ";
                size_t playlistChoice;
                std::cin >> playlistChoice;
                std::cin.ignore();

                if (playlistChoice > 0 && playlistChoice <= playlists.size()) {
                    if (currentUser->addSongToPlaylist(playlists[playlistChoice-1].getName(),
                                                       *results[choice-1])) {
                        std::cout << "Song added to playlist!\n";
                    } else {
                        std::cout << "Failed to add song.\n";
                    }
                } else {
                    std::cout << "Invalid choice.\n";
                }
            }
            std::cin.get();
        }
    }
}

void MusicPlayerSystem::showArtists() {
    clearScreen();
    const auto& artists = admin.getArtists();
    if (artists.empty()) {
        std::cout << "No artists available.\n";
        std::cin.get();
        return;
    }

    std::cout << "=== Artists ===\n";
    for (size_t i = 0; i < artists.size(); ++i) {
        std::cout << i+1 << ". " << artists[i].getName() << "\n";
    }

    std::cout << "\nEnter artist number to view details (0 to go back): ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice > 0 && choice <= artists.size()) {
        clearScreen();
        artists[choice-1].displayProfile();
        std::cout << "\nPress enter to continue...";
        std::cin.get();
    }
}

void MusicPlayerSystem::displaySongs(const std::vector<Song*>& songs) const {
    for (size_t i = 0; i < songs.size(); ++i) {
        std::cout << i+1 << ". " << songs[i]->getTitle()
                  << " - " << songs[i]->getArtist() << "\n";
    }
}
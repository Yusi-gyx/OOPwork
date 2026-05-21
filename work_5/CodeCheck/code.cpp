#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
using namespace std;

class Song {
    string title;
    string artist;
    int duration;
public:
    Song(string t, string a, int d)
        : title(t), artist(a), duration(d) {}

    virtual ~Song() = default;

    const string& getTitle() const { return title; }
    const string& getArtist() const { return artist; }
    int getDuration() const { return duration; }

    virtual string display() const {
        return title + " - " + artist;
    }
};

class PremiumSong : public Song {
    bool lossless;
public:
    PremiumSong(string t, string a, int d, bool hi)
        : Song(t, a, d), lossless(hi) {}

    string display() const override {
        return Song::display() + (lossless ? " [Hi-Res]" : "");
    }
};

class Playlist {
    string name;
    vector<shared_ptr<Song>> songs;
    map<string, int> playCount;

public:
    Playlist(const string& n) : name(n) {}

    void addSong(shared_ptr<Song> song) {
        songs.push_back(song);
    }

    void recordPlay(const string& title) {
        playCount[title]++;
    }

    void removeByArtist(const string& artist) {
        for (auto it = songs.begin(); it != songs.end(); ++it) {
            if ((*it)->getArtist() == artist) {
                songs.erase(it);
            }
        }
    }

    int getPlayCount(const string& title) const {
        return playCount.at(title);
    }

    void generateRecommendations(int minPlays) {
        for (auto& song : songs) {
            if (playCount[song->getTitle()] >= minPlays) {
                songs.push_back(make_shared<Song>(*song));
            }
        }
    }

    void transferSong(shared_ptr<Song> song, Playlist& target) {
        target.addSong(std::move(song));
        cout << "Transferred: " << song->display() << endl;
    }

    void printAll() const {
        cout << "=== " << name << " ===" << endl;
        for (const auto& s : songs) {
            cout << "  " << s->display() << endl;
        }
    }
};

class MusicLibrary {
    vector<shared_ptr<Playlist>> playlists;

public:
    void addPlaylist(shared_ptr<Playlist> pl) {
        playlists.push_back(pl);
    }

    void importSong(Playlist& pl) {
        Song* raw = new PremiumSong("Bohemian Rhapsody", "Queen", 354, true);
        shared_ptr<Song> sp1(raw);
        shared_ptr<Song> sp2(raw);
        pl.addSong(sp1);
        pl.addSong(sp2);
    }

    void showAll() const {
        for (const auto& pl : playlists) {
            pl->printAll();
        }
    }
};

void displaySong(Song song) {
    cout << song.display() << endl;
}

int main() {
    MusicLibrary lib;

    auto pl = make_shared<Playlist>("My Favorites");

    auto s1 = make_shared<PremiumSong>("Yesterday", "Beatles", 123, true);
    auto s2 = make_shared<Song>("Hey Jude", "Beatles", 431);

    pl->addSong(s1);
    pl->addSong(s2);

    displaySong(*s1);

    pl->removeByArtist("Beatles");

    lib.addPlaylist(pl);
    lib.showAll();

    return 0;
}

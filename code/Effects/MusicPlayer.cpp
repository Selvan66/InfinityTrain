/** @file MusicPlayer.cpp */
#include <cassert>

#include "Effects/MusicPlayer.h"


MusicPlayer::MusicPlayer()
: mMusic()
, mPlayedMusic(MusicsID::None)
, mFilenames()
, mVolume(0.f)
{
    mFilenames[MusicsID::Menu] = "musics/menu.ogg";
    mFilenames[MusicsID::Game] = "musics/game.ogg";
}

void MusicPlayer::play(MusicsID id)
{
    mPlayedMusic = id;
    std::string filename = mFilenames[id];
    bool isOpen = mMusic.openFromFile(filename);
    assert(isOpen);

    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
    mMusic.play();
}

void MusicPlayer::stop()
{
    mMusic.stop();
}

void MusicPlayer::setPaused(bool paused)
{
    if (paused) 
    {
        mMusic.pause();
    } 
    else 
    {
        mMusic.play();
    }
}

void MusicPlayer::setVolume(float volume)
{
    mVolume = volume;
}

void MusicPlayer::replay()
{
    if (mPlayedMusic != MusicsID::None)
        play(mPlayedMusic);
}

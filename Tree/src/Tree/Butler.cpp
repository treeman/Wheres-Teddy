#include "Tree/Butler.hpp"
#include "Tree/Game.hpp"

using Tree::Butler;

boost::shared_ptr<Butler> Tree::GetButler()
{
    return GAME->GetButler();
}

Butler::Butler()
{

}
Butler::~Butler()
{

}

void Butler::LoadSprites( std::string lua_file )
{
    spr_loader.Load( lua_file );
}

boost::shared_ptr<sf::Font> Butler::GetFont( std::string path,
    unsigned int size ) throw( Error::file_not_found )
{
    typedef std::pair<FontMap::iterator, FontMap::iterator> ItPair;

    //find all fonts with the same font file
    ItPair ret = font_map.equal_range( path );
    if( ret.first != ret.second ) {

        //search for the same font size
        //it's important because otherwise they'll get blurry and ugly
        for( FontMap::iterator it = ret.first; it != ret.second; ++it ) {
            if( it->second->GetCharacterSize() == size ) {
                return it->second;
            }
        }
    }
    boost::shared_ptr<sf::Font> fnt( new sf::Font() );

    if( !fnt->LoadFromFile( path.c_str(), size ) ) {
        std::string s = "Unable to load font: '" + path + "'";
        throw( Error::file_not_found( s.c_str() ) );
    }

    font_map.insert( std::make_pair( path, fnt ) );
    return fnt;
}

boost::shared_ptr<sf::Image> Butler::GetImage( std::string path )
    throw( Error::file_not_found )
{
    ImageMap::iterator it = image_map.find( path );
    if( it != image_map.end() ) {
        return it->second;
    }
    else {
        boost::shared_ptr<sf::Image> img( new sf::Image() );

        if( !img->LoadFromFile( path.c_str() ) ) {
            std::string s = "Unable to load image: '" + path + "'";
            throw( Error::file_not_found( s.c_str() ) );
        }

        image_map.insert( std::make_pair( path, img ) );
        return img;
    }
}

boost::shared_ptr<sf::Music> Butler::GetMusic( std::string path )
    throw( Error::file_not_found )
{
    MusicMap::iterator it = music_map.find( path );
    if( it != music_map.end() ) {
        return it->second;
    }
    else {
        boost::shared_ptr<sf::Music> music( new sf::Music() );

        if( !music->OpenFromFile( path.c_str() ) ) {
            std::string s = "Unable to load music: '" + path + "'";
            throw( Error::file_not_found( s.c_str() ) );
        }

        music_map.insert( std::make_pair( path, music ) );
        return music;
    }
}

boost::shared_ptr<sf::SoundBuffer> Butler::GetSoundBuffer( std::string path )
    throw( Error::file_not_found )
{
    SoundBufferMap::iterator it = soundbuffer_map.find( path );
    if( it != soundbuffer_map.end() ) {
        return it->second;
    }
    else {
        boost::shared_ptr<sf::SoundBuffer> soundbuffer( new sf::SoundBuffer() );

        if( !soundbuffer->LoadFromFile( path.c_str() ) ) {
            std::string s = "Unable to load soundbuffer: '" + path + "'";
            throw( Error::file_not_found( s.c_str() ) );
        }

        soundbuffer_map.insert( std::make_pair( path, soundbuffer ) );
        return soundbuffer;
    }
}

Tree::Sprite Butler::GetSprite( std::string name )
{
    return spr_loader.Get( name );
}

sf::Sound Butler::GetSound( std::string path )
{
    return sf::Sound( *GetSoundBuffer( path ) );
}


from distutils.core import setup, Extension

module1 = Extension('song_artist_search',
	include_dirs = ['/usr/local/include'],
	libraries = ['pthread'],		
	sources = ['song_artist_searchmodule.c'])

setup (name = 'SongAndArtistSearchFunction',
       version = '1.0',
       author = 'Bhishma',
       description = 'Searches music repository by song name and artist name',
       ext_modules = [module1])

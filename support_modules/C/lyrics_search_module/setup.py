from distutils.core import setup, Extension

module1 = Extension('lyricsSearch',
	include_dirs = ['/usr/local/include'],
	libraries = ['pthread'],		
	sources = ['lyricsSearchmodule.c'])

setup (name = 'LyricsSearchFunction',
       version = '1.0',
       author = 'Vedant',
       description = 'Searches music repository by lyrics',
       ext_modules = [module1])

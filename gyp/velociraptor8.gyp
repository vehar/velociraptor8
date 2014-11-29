{
	'targets': [
		{
			'target_name': 'Velociraptor8',
			'type': 'executable',
			'msvs_disabled_warnings': [4244],
			'dependencies': [
				'scintilla.gyp:Scintilla',
				'../../sumatrapdf/gyp/utils.gyp:utils'
			],
			'defines': [
				'NO_LIBMUPDF',
				'NO_LIBWEBP',
				'WIN32',
				'STATIC_BUILD',
				'SCI_LEXER',
				'BOOKMARK_EDITION',
				'_CRT_SECURE_NO_WARNINGS',
				'_UNICODE',
				'UNICODE',
			],
			'include_dirs': [
				"../src",
				"../src/utils",
			],
			'link_settings': {
				'libraries': [
					'gdiplus.lib',
					'comctl32.lib',
					'shlwapi.lib',
					'Version.lib',
					'user32.lib',
					'kernel32.lib',
					'gdi32.lib',
					'ole32.lib',
					'advapi32.lib',
					'shell32.lib',
					'oleaut32.lib',
					'winspool.lib',
					'comdlg32.lib',
					'urlmon.lib',
					'windowscodecs',
					'wininet',
					'msimg32',
					'imm32',
				],
			},
			'msvs_settings': {
			  'VCLinkerTool': {
				'SubSystem': '2', # windows
			  },
			},
			'sources': [
				"../src/Common.h",
				"../src/Dialogs.cpp",
				"../src/Dialogs.h",
				"../src/Dlapi.cpp",
				"../src/Dlapi.h",
				"../src/Edit.cpp",
				"../src/Edit.h",
				"../src/FileUtil2.cpp",
				"../src/FileUtil2.h",
				"../src/Helpers.cpp",
				"../src/Helpers.h",
				"../src/Http.cpp",
				"../src/Http.h",
				"../src/Install.cpp",
				"../src/Install.h",
				"../src/Menu.cpp",
				"../src/Menu.h",
				"../src/Print.cpp",
				"../src/resource.h",
				"../src/SciCall.h",
				"../src/StrUtil2.cpp",
				"../src/StrUtil2.h",
				"../src/Styles.cpp",
				"../src/Styles.h",
				"../src/TableLayout.cpp",
				"../src/TableLayout.h",
				"../src/TextFormat.cpp",
				"../src/TextFormat.h",
				"../src/Translations.cpp",
				"../src/Translations.h",
				"../src/ve8.cpp",
				"../src/ve8.h",
				"../src/Version.h",
				"../src/VersionRev.h",
				"../src/WinUtil2.cpp",
				"../src/WinUtil2.h",
				"../src/Notepad2.rc",
				"../src/Notepad2.ver",
				"../res/Copy.cur",
				"../res/Encoding.bmp",
				"../res/Next.bmp",
				"../res/Open.bmp",
				"../res/Pick.bmp",
				"../res/Prev.bmp",
				"../res/Run.ico",
				"../res/Styles.ico",
				"../res/Toolbar.bmp",
				"../res/Toolbar1.bmp",
				"../res/Toolbar2.bmp",
				"../res/velociraptor8.ico",
			],
		},
	],
}

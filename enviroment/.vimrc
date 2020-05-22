" Only modify vim for a framework enviroment
if !empty( glob( $FRAMEWORK ))

	" Change the color of the comments
	syntax on
	hi Comment  ctermfg=blue

	" Turn off the sound
	set belloff=all

	" Enable NERDTree shortcut
	nmap <F7> :NERDTreeToggle<CR>

	" Enable Tagbar shortcut
	if !empty( glob( $FRAMEWORK_TAGS ))
		set tags=tags;,$FRAMEWORK_TAGS
		nmap <F8> :TagbarToggle<CR>
	endif
endif



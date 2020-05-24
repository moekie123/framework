" Only modify vim for a framework enviroment
if !empty( glob( $FRAMEWORK ))

	" Disable Swap-Files
	set noswapfile

	" Change the color of the comments
	syntax on
	hi Comment  ctermfg=blue

	" Turn off the sound
	set belloff=all

	" Load framework enviroment
	let $BASH_ENV = "~/.bash_profile"

	" Enable TermDebug shortcut
	packadd termdebug

	let BINARY=$FRAMEWORK."/binary/".$SESSION
	nmap <F6> :Termdebug <c-r>=BINARY<cr><CR>

	let g:termdebug_popup = 0
	let g:termdebug_wide = 100

	" Enable NERDTree shortcut
	nmap <F7> :NERDTreeToggle<CR>

	" Enable Tagbar shortcut
	if !empty( glob( $FRAMEWORK_TAGS ))
		set tags=tags;,$TAGS
		nmap <F8> :TagbarToggle<CR>
	endif

endif



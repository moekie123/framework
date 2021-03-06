" Only modify vim for a framework enviroment
if !empty( glob( $FRAMEWORK ))

	" Change the color of the comments
	syntax on
	hi Comment  ctermfg=blue

	" Turn off the sound
	set belloff=all

	" Load framework enviroment
	let $BASH_ENV = "~/.bash_profile"

	" Enable TermDebug shortcut
	packadd termdebug

	let BINARY=$FRAMEWORK."/binary/".$FRAMEWORK_MODULE
	nmap <F6> :Termdebug <c-r>=BINARY<cr><CR>

	let g:termdebug_popup = 0
	let g:termdebug_wide = 163

	" Enable NERDTree shortcut
	nmap <F7> :NERDTreeToggle<CR>

	" Enable Tagbar shortcut
	if !empty( glob( $FRAMEWORK_TAGS ))
		set tags=tags;,$FRAMEWORK_TAGS
		nmap <F8> :TagbarToggle<CR>
	endif

endif



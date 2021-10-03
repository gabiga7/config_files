"use terminal in vim"
packadd termdebug

"Syntaxic coloration"
syntax on
colorscheme torte

"Enable filetype detection for plugins and indent option"
filetype plugin indent on

"Set length to 80 and auto-return"
set textwidth=80
set wrap
set colorcolumn=80

"Enable line number"
set number

"Tabulation and indentation options"
set shiftwidth=4
set softtabstop=-1
set expandtab
set autoindent

"Auto-close parenthesis"
inoremap " ""<left>
inoremap ' ''<left>
inoremap ( ()<left>
inoremap [ []<left>
inoremap { {}<left>
inoremap {<CR> {<CR>}<ESC>O
inoremap {;<CR> {<CR>};<ESC>O

"Call the .vimrc.plug file""
if filereadable(expand("~/.vimrc.plug"))
    source ~/.vimrc.plug
endif

"Shortcut to remove errors"
"noremap <F5> :CleanupMarkErrors<CR>
"noremap <F4> :MarkErrors<CR>

"Shortcut gcc execution"
noremap <F6> :w<CR> :!clear<CR> :!gcc % -o -Wextra -Wall -Werror -std=c99 -pedantic %< && ./%<<CR>


"Shortcut ; end of line"
noremap ; <ESC>A;<ESC><left>


"Shortcut insert test up
noremap <S-F12> <ESC>Oprintf("test\n");<ESC><left>

"Shortcut insert test down
noremap <F12> <ESC>oprintf("test\n");<ESC><left>

"Shortcut comment to end
noremap <F5> o/*<ESC>Go*/<ESC><left> 

noremap œ <ESC>:w<CR> 

"Shortcut insert main function
noremap <F4> oint main(void)<ESC>o{<CR><CR>return 0;<CR>}<ESC><up><up>i<Tab><ESC>

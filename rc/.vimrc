"use terminal in vim";
packadd termdebug

"Syntaxic coloration"
syntax on
colorscheme torte

"Remember last position
if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif

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
"noremap <F6> :w<CR> :!clear<CR> :!gcc % -o -Wextra -Wall -Werror -std=c99 -pedantic %< && ./%<<CR>

"Make mouse usable
set mouse=r

"Shortcut ; end of line"
noremap ; <ESC>A;<ESC><left>

"Shortcut indentation back to line
noremap gg=G gg=G''

"Shortcut insert test up
noremap <S-F12> <ESC>Oprintf("test\n");<ESC><left>

"Shortcut insert test down
noremap <F12> <ESC>oprintf("test\n");<ESC><left>

"Shortcut comment to end
noremap <F5> o/*<ESC>Go*/<ESC><left> 

"Shortcut to save
noremap ² <ESC>:w<CR> 

"Shortcut insert main function
noremap <F4> oint main(void)<ESC>o{<CR><CR>return 0;<CR>}<ESC><up><up>i<Tab><ESC>

"Disable Page Up and Down
noremap <PageUp> <Nop>
noremap <PageDown> <Nop>


"Shortcut execution test with leak detector
noremap <C-e> <ESC>:w<CR>:!~/scripts/execute.sh % &<CR><CR><ESC>:w<CR>:!~/scripts/regex/main % &<CR><ESC>:sleep 250ms<CR>:e<CR>

"Shortcut debug test with leak detector
noremap <C-d> <ESC>:w<CR>:!~/scripts/debug.sh % &<CR><CR><ESC>:w<CR>:!~/scripts/regex/main % &<CR><ESC>:sleep 250ms<CR>:e<CR>

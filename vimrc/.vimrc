set nu

if(has("win32") || has("win95") || has("win64") || has("win16")) "判定当前操作系统类型
    let g:iswindows=1
else
    let g:iswindows=0
endif

autocmd BufEnter * lcd %:p:h

set nocompatible "不要vim模仿vi模式，建议设置，否则会有很多不兼容的问题
syntax on"打开高亮
if has("autocmd")
    filetype plugin indent on "根据文件进行缩进
    augroup vimrcEx
        au!
        autocmd FileType text setlocal textwidth=78
        autocmd BufReadPost *
                    \ if line("'\"") > 1 && line("'\"") <= line("$") |
                    \ exe "normal! g`\"" |
                    \ endif
    augroup END
else
    "智能缩进，相应的有cindent，官方说autoindent可以支持各种文件的缩进，但是效果会比只支持C/C++的cindent效果会差一点，但笔者并没有看出来
    set autoindent " always set autoindenting on 
endif " has("autocmd")

set expandtab
set tabstop=4 "让一个tab等于4个空格
set softtabstop=4
set shiftwidth=4

set vb t_vb=
set nowrap "不自动换行
set hlsearch "高亮显示结果
set incsearch "在输入要搜索的文字时，vim会实时匹配
set backspace=indent,eol,start whichwrap+=<,>,[,] "允许退格键的使用
if(g:iswindows==1) "允许鼠标的使用
    "防止linux终端下无法拷贝
    if has('mouse')
        set mouse=a
    endif
    au GUIEnter * simalt ~x
endif
"字体的设置
set guifont=Bitstream_Vera_Sans_Mono:h9:cANSI "记住空格用下划线代替哦
set gfw=幼圆:h10:cGB2312



"""""""""""""""""""""""""""""单个文件编译 按F5编译单个源文件，按F6执行make
map <F5> :call Do_OneFileMake()<CR>
function Do_OneFileMake()
    if expand("%:p:h")!=getcwd()
        echohl WarningMsg | echo "Fail to make! This file is not in the current dir! Press <F7> to redirect to the dir of this file." | echohl None
        return
    endif
    let sourcefileename=expand("%:t")
    if (sourcefileename=="" || (&filetype!="cpp" && &filetype!="c"))
        echohl WarningMsg | echo "Fail to make! Please select the right file!" | echohl None
        return
    endif
    let deletedspacefilename=substitute(sourcefileename,' ','','g')
    if strlen(deletedspacefilename)!=strlen(sourcefileename)
        echohl WarningMsg | echo "Fail to make! Please delete the spaces in the filename!" | echohl None
        return
    endif
    if &filetype=="c"
        if g:iswindows==1
            set makeprg=gcc\ -o\ %<.exe\ %
        else
            set makeprg=gcc\ -o\ %<\ %
        endif
    elseif &filetype=="cpp"
        if g:iswindows==1
            set makeprg=g++\ -o\ %<.exe\ %
        else
            set makeprg=g++\ -o\ %<\ %
        endif
        "elseif &filetype=="cs"
        "set makeprg=csc\ \/nologo\ \/out:%<.exe\ %
    endif
    if(g:iswindows==1)
        let outfilename=substitute(sourcefileename,'\(\.[^.]*\)' ,'.exe','g')
        let toexename=outfilename
    else
        let outfilename=substitute(sourcefileename,'\(\.[^.]*\)' ,'','g')
        let toexename=outfilename
    endif
    if filereadable(outfilename)
        if(g:iswindows==1)
            let outdeletedsuccess=delete(getcwd()."\\".outfilename)
        else
            let outdeletedsuccess=delete("./".outfilename)
        endif
        if(outdeletedsuccess!=0)
            set makeprg=make
            echohl WarningMsg | echo "Fail to make! I cannot delete the ".outfilename | echohl None
            return
        endif
    endif
    execute "silent make"
    set makeprg=make
    execute "normal :"
    if filereadable(outfilename)
        if(g:iswindows==1)
            execute "!".toexename
        else
            execute "!./".toexename
        endif
    endif
    execute "copen"
endfunction
"进行make的设置
map <F6> :call Do_make()<CR>
map <F7> :call Do_make_clean()<CR>
function Do_make()
    let dir=getcwd()."/"
    while !filereadable(dir."Makefile") && !filereadable(dir."makefile")
        "echo dir
        let dir=DirName(dir)
        if (dir=="")
            echo "no Makefile!!!" 
            return
        endif
    endwhile
    set makeprg=make
    execute "make -j4 -C ".dir
    "execute "copen"   " make完后不打开小窗口
endfunction

function Do_make_clean()
    let dir=getcwd()."/"
    while !filereadable(dir."Makefile") && !filereadable(dir."makefile")
        "echo dir
        let dir=DirName(dir)
        if (dir=="")
            echo "no Makefile!!!" 
            return
        endif
    endwhile
    execute "make clean -C ".dir
endfunction

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

set go="无菜单、工具栏"


""""""""""""""""设置中文编码不出现乱码
set encoding=utf-8 fileencodings=ucs-bom,utf-8,cp936,gb2312,gbk  "设置自动识别文件编码  不设置可能会出现中文乱码 


"""""""""""""""""""""""设置cscope
map <F12> :call Do_CsTag()<CR>
"nmap <C-@>s :cs find s <C-R>=expand("<cword>")<CR><CR>:copen<CR>
"nmap <C-@>g :cs find g <C-R>=expand("<cword>")<CR><CR>
"nmap <C-@>c :cs find c <C-R>=expand("<cword>")<CR><CR>:copen<CR>
"nmap <C-@>t :cs find t <C-R>=expand("<cword>")<CR><CR>:copen<CR>
"nmap <C-@>e :cs find e <C-R>=expand("<cword>")<CR><CR>:copen<CR>
"nmap <C-@>f :cs find f <C-R>=expand("<cfile>")<CR><CR>:copen<CR>
"nmap <C-@>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>:copen<CR>
"nmap <C-@>d :cs find d <C-R>=expand("<cword>")<CR><CR>:copen<CR>
nmap cs :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap cg :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap cc :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap ct :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap ce :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap cf :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap ci :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
nmap cd :cs find d <C-R>=expand("<cword>")<CR><CR>

function DirName(path)
    if(a:path=="/")
        return ""
    endif
    let list=split(a:path, "/")
    :call remove(list,-1)
    if(empty(list))
        return "/"
    endif
    let dir="/".join(list,"/")."/"
    return dir
endfunction

function Do_CsTag()
    let dir = getcwd()."/"
    while !filereadable(dir."tags") 
        "echo dir
        let dir=DirName(dir)
        if (dir=="")
            echo "no tags!!!" 
            return
        endif
    endwhile
    echohl WarningMsg | echo dir."tags" | echohl None
    if filereadable(dir."tags")
        let tagsdeleted=delete(dir."tags")
        if(tagsdeleted!=0)
            echohl WarningMsg | echo "Fail to do tags! I cannot delete the tags" | echohl None
            return
        endif
    endif
    if has("cscope")
        silent! execute "cs kill -1"
    endif
    if filereadable(dir."cscope.files")
        let csfilesdeleted=delete(dir."cscope.files")
        if(csfilesdeleted!=0)
            echohl WarningMsg | echo "Fail to do cscope! I cannot delete the cscope.files" | echohl None
            return
        endif
    endif
    if filereadable(dir."cscope.out")
        let csoutdeleted=delete(dir."cscope.out")
        if(csoutdeleted!=0)
            echohl WarningMsg | echo "Fail to do cscope! I cannot delete the cscope.out" | echohl None
            return
        endif
    endif
    if(executable('ctags'))
        execute "!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q -f ".dir."tags ".dir
        silent! execute "set tag=".dir."tags"
    endif
    if(executable('cscope') && has("cscope") )
        silent! execute "!find ".dir." -name '*.h' -o -name '*.c' -o -name '*.cpp' -o -name '*.java' -o -name '*.cc' > ".dir."cscope.files"
        silent! execute "!cscope  -bkq -f ".dir."cscope.out -i ".dir."cscope.files"
        execute "normal :"
        if filereadable(dir."cscope.out")
            execute "cs add ".dir."cscope.out"
        endif
    endif
endfunction

"进行Tlist的设置
""TlistUpdate可以更新tags
"map <F3> :silent! Tlist<CR> "按下F3就可以呼出了

let Tlist_Ctags_Cmd='ctags' "因为我们放在环境变量里，所以可以直接执行
let Tlist_Use_Right_Window=0 "让窗口显示在右边，0的话就是显示在左边
let Tlist_Show_One_File=1 "让taglist可以同时展示多个文件的函数列表，如果想只有1个，设置为1
let Tlist_File_Fold_Auto_Close=1 "非当前文件，函数列表折叠隐藏
let Tlist_Exit_OnlyWindow=1 "当taglist是最后一个分割窗口时，自动推出vim
let Tlist_Process_File_Always=0 "是否一直处理tags.1:处理;0:不处理。不是一直实时更新tags，因为没有必要
let Tlist_Inc_Winwidth=0


" WinManager的设置
" 界面分割
" let g:winManagerWindowLayout = "TagList|FileExplorer,BufExplorer"
let g:winManagerWindowLayout = "TagList"
 
"设置winmanager的宽度，默认为25
let g:winManagerWidth = 40
"定义打开关闭winmanager按键
"按F3时这里会调用taglist
nmap <silent> <F3> :WMToggle<cr>  

set so=8

let g:miniBufExplMapWindowNavVim=1 
let g:miniBufExplMapWindowNavArrows=1 
let g:miniBufExplMapCTabSwitchBufs=1 
let g:miniBufExplModSelTarget=1 

set t_Co=256
"colorscheme darkburn
colorscheme wombat256mod

set ignorecase " 搜索时忽略大小写


" DoxygenToolkt设置
" :Doxy 生成函数或类的注释
" :DoxAuthor 生成文件的作者信息
" :DoxLic 生成License
let g:DoxygenToolkit_authorName="litang"
let g:DoxygenToolkit_briefTag_pre="@brief "
let g:DoxygenToolkit_paramTag_ptr="@param "
let g:DoxygenToolkit_returnTag="@return "



nmap pp :ptag <C-R><C-W><cr><C-r><C-w>
nmap px :pclose<cr>
nmap cp :copen<cr>
nmap cx :cclose<cr>


" 关掉智能补全时的预览窗口
set completeopt=longest,menu


" 自动补全
let g:SuperTabRetainCompletionType=2
" 0 - 不记录上次的补全方式
" 1 - 记住上次的补全方式,直到用其他的补全命令改变它
" 2 - 记住上次的补全方式,直到按ESC退出插入模式为止
let g:SuperTabDefaultCompletionType="<C-X><C-O>"


" 按F8在文件中搜索光标所在单词
nnoremap <silent> <F8> :Grep<CR>

" for OmniCppComplete  
set nocp
filetype plugin on

" for mark.vim
let mapleader="m"
nmap <Leader>M <Plug>MarkToggle
nmap <Leader>N <Plug>MarkAllClear

set nu

if(has("win32") || has("win95") || has("win64") || has("win16")) "�ж���ǰ����ϵͳ����
    let g:iswindows=1
else
    let g:iswindows=0
endif

autocmd BufEnter * lcd %:p:h

set nocompatible "��Ҫvimģ��viģʽ���������ã�������кܶ಻���ݵ�����
syntax on"�򿪸���
if has("autocmd")
    filetype plugin indent on "�����ļ���������
    augroup vimrcEx
        au!
        autocmd FileType text setlocal textwidth=78
        autocmd BufReadPost *
                    \ if line("'\"") > 1 && line("'\"") <= line("$") |
                    \ exe "normal! g`\"" |
                    \ endif
    augroup END
else
    "������������Ӧ����cindent���ٷ�˵autoindent����֧�ָ����ļ�������������Ч�����ֻ֧��C/C++��cindentЧ�����һ�㣬�����߲�û�п�����
    set autoindent " always set autoindenting on 
endif " has("autocmd")

set expandtab
set tabstop=4 "��һ��tab����4���ո�
set softtabstop=4
set shiftwidth=4

set vb t_vb=
set nowrap "���Զ�����
set hlsearch "������ʾ���
set incsearch "������Ҫ����������ʱ��vim��ʵʱƥ��
set backspace=indent,eol,start whichwrap+=<,>,[,] "�����˸����ʹ��
if(g:iswindows==1) "��������ʹ��
    "��ֹlinux�ն����޷�����
    if has('mouse')
        set mouse=a
    endif
    au GUIEnter * simalt ~x
endif
"���������
set guifont=Bitstream_Vera_Sans_Mono:h9:cANSI "��ס�ո����»��ߴ���Ŷ
set gfw=��Բ:h10:cGB2312



"""""""""""""""""""""""""""""�����ļ����� ��F5���뵥��Դ�ļ�����F6ִ��make
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
"����make������
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
    "execute "copen"   " make��󲻴�С����
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

set go="�޲˵���������"


""""""""""""""""�������ı��벻��������
set encoding=utf-8 fileencodings=ucs-bom,utf-8,cp936,gb2312,gbk  "�����Զ�ʶ���ļ�����  �����ÿ��ܻ������������ 


"""""""""""""""""""""""����cscope
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

"����Tlist������
""TlistUpdate���Ը���tags
"map <F3> :silent! Tlist<CR> "����F3�Ϳ��Ժ�����

let Tlist_Ctags_Cmd='ctags' "��Ϊ���Ƿ��ڻ�����������Կ���ֱ��ִ��
let Tlist_Use_Right_Window=0 "�ô�����ʾ���ұߣ�0�Ļ�������ʾ�����
let Tlist_Show_One_File=1 "��taglist����ͬʱչʾ����ļ��ĺ����б������ֻ��1��������Ϊ1
let Tlist_File_Fold_Auto_Close=1 "�ǵ�ǰ�ļ��������б��۵�����
let Tlist_Exit_OnlyWindow=1 "��taglist�����һ���ָ��ʱ���Զ��Ƴ�vim
let Tlist_Process_File_Always=0 "�Ƿ�һֱ����tags.1:����;0:����������һֱʵʱ����tags����Ϊû�б�Ҫ
let Tlist_Inc_Winwidth=0


" WinManager������
" ����ָ�
" let g:winManagerWindowLayout = "TagList|FileExplorer,BufExplorer"
let g:winManagerWindowLayout = "TagList"
 
"����winmanager�Ŀ�ȣ�Ĭ��Ϊ25
let g:winManagerWidth = 40
"����򿪹ر�winmanager����
"��F3ʱ��������taglist
nmap <silent> <F3> :WMToggle<cr>  

set so=8

let g:miniBufExplMapWindowNavVim=1 
let g:miniBufExplMapWindowNavArrows=1 
let g:miniBufExplMapCTabSwitchBufs=1 
let g:miniBufExplModSelTarget=1 

set t_Co=256
"colorscheme darkburn
colorscheme wombat256mod

set ignorecase " ����ʱ���Դ�Сд


" DoxygenToolkt����
" :Doxy ���ɺ��������ע��
" :DoxAuthor �����ļ���������Ϣ
" :DoxLic ����License
let g:DoxygenToolkit_authorName="litang"
let g:DoxygenToolkit_briefTag_pre="@brief "
let g:DoxygenToolkit_paramTag_ptr="@param "
let g:DoxygenToolkit_returnTag="@return "



nmap pp :ptag <C-R><C-W><cr><C-r><C-w>
nmap px :pclose<cr>
nmap cp :copen<cr>
nmap cx :cclose<cr>


" �ص����ܲ�ȫʱ��Ԥ������
set completeopt=longest,menu


" �Զ���ȫ
let g:SuperTabRetainCompletionType=2
" 0 - ����¼�ϴεĲ�ȫ��ʽ
" 1 - ��ס�ϴεĲ�ȫ��ʽ,ֱ���������Ĳ�ȫ����ı���
" 2 - ��ס�ϴεĲ�ȫ��ʽ,ֱ����ESC�˳�����ģʽΪֹ
let g:SuperTabDefaultCompletionType="<C-X><C-O>"


" ��F8���ļ�������������ڵ���
nnoremap <silent> <F8> :Grep<CR>

" for OmniCppComplete  
set nocp
filetype plugin on

" for mark.vim
let mapleader="m"
nmap <Leader>M <Plug>MarkToggle
nmap <Leader>N <Plug>MarkAllClear

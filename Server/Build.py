# ----------------------------------------------------------------------------
# $File: Build.py for compile project $
# $Date: 20.01.2020 $
# $Revision: 20.01.2020 $
# $Creator: 0xlay $
# ----------------------------------------------------------------------------
import os

main_direct = os.getcwd()
build_direct = 'temp-build'
name_project = 'Server_RemoteUnixTerminal'

# if os.mkdir(build_direct) == 17:
#     os.system('rm -R ' + build_direct)
try:
    os.mkdir(build_direct)
except OSError:
    print('Folder exist...\n')

move = 'cd ' + main_direct + '/' + build_direct 
copy = 'cp -f ' + name_project + ' ' + main_direct
build_command = move + ' && cmake .. && make && ' +  copy

os.system(build_command)
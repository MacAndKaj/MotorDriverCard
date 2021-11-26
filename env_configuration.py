import xml.etree.ElementTree as ET
from shutil import copy, rmtree
from pathlib import Path
import os, argparse
"""
    
    Script for configuring

"""
MIDDLEWARES_DIR = 'Middlewares'
DRIVERS_DIR = 'Drivers'

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--path', required=False, type=str, default=str(Path.home()),
                        help='Path to STM32Cube repository.')

    args = parser.parse_args()

    if os.path.exists(MIDDLEWARES_DIR):
        rmtree(MIDDLEWARES_DIR)

    if os.path.exists(DRIVERS_DIR):
        rmtree(DRIVERS_DIR)

    references_config = ET.parse('./.project')

    def correct_xml_element(elem):
        return elem is not None and len(elem) != 0

    files_to_move = filter(correct_xml_element,
                           [elem.text for elem in references_config.findall('linkedResources/link/location')])
    
    def not_duplicated_files(elem):
        return 'PARENT-1-PROJECT_LOC/' in elem

    files_to_move = filter(not_duplicated_files, files_to_move)
    
    files_to_move = [file_path.replace('PARENT-1-PROJECT_LOC/', '') for file_path in files_to_move]

    old_to_new_path = {}
    stm32cube_path = args.path
    for file_path in files_to_move:
        drivers_begin = file_path.find("Drivers")
        if drivers_begin != -1:
            old_to_new_path[file_path.replace('~', stm32cube_path)] = './' + file_path[drivers_begin:]
            continue

        middlewares_begin = file_path.find("Middlewares")
        if middlewares_begin != -1:
            old_to_new_path[file_path.replace('~', stm32cube_path)] = './' + file_path[middlewares_begin:]

    for old_path, new_path in old_to_new_path.items():
        new_directory = new_path[0:new_path.rfind('/')]
        print("Copied " + old_path + " to " + new_path)
        if not os.path.exists(new_directory):
            os.makedirs(new_directory)
        copy(old_path, new_directory)

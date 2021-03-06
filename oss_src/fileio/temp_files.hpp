/**
 * Copyright (C) 2016 Turi
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license. See the LICENSE file for details.
 */
#ifndef FILEIO_TEMP_FILE_HPP 
#define FILEIO_TEMP_FILE_HPP 
#include <string>
#include <vector>

namespace graphlab {

/**
 * Get the current system user name.
 */
std::string get_system_user_name();

/**
 * Returns a file name which can be used for a temp file.
 * Returns an empty string on failure, a temporary file name on success.
 * The file name returned is allowed to be a "prefix". i.e. arbitrary extensions
 * can be attached to be tail of the file. For instance, if get_temp_name()
 * returns /tmp/file51apTO, you can use /tmp/file51apTO.csv
 *
 * \param prefix Optional. If specified, this exact prefix will be returned in
 * the temporary path. ex: /var/tmp/graphlab-ylow/12345/[prefix]. If an empty 
 * string or not specified, a random unique prefix will be generated.
 *
 * \param _prefer_hdfs Optional, defaults to false. If true, prefers to use
 * HDFS if available.
 *
 * Note that if you specify your own prefix it is up to you to manage collisions,
 * i.e. multiple parts of the program using the same prefix for instance.
 */
std::string get_temp_name(const std::string& prefix="", bool _prefer_hdfs=false);

/**
 * Same as get_temp_name but return the temp file
 * on hdfs if avaiable. The hdfs temp file location is a runtime configurable
 * variable GRAPHLAB_CACHE_FILE_HDFS_LOCATION defined in fileio_constant.hpp.
 *
 * \param prefix Optional. If specified, this exact prefix will be returned in
 * the temporary path. ex: /var/tmp/graphlab-ylow/12345/[prefix]. If an empty 
 * string or not specified, a random unique prefix will be generated.
 *
 * Note that if you specify your own prefix it is up to you to manage collisions,
 * i.e. multiple parts of the program using the same prefix for instance.
 */
std::string get_temp_name_prefer_hdfs(const std::string& prefix="");

/**
 * Deletes the temporary file with the name s. 
 * Returns true on success, false on failure (file does not exist, 
 * or cannot be deleted). The file will only be deleted
 * if a prefix of s was previously returned by get_temp_name(). This is done 
 * for safety to prevent this function from being used to delete arbitrary files.
 *
 * For instance, if get_temp_name() previously returned /tmp/file51apTO ,
 * delete_temp_file will succeed on /tmp/file51apTO.csv . delete_temp_file will
 * fail on stuff like /usr/bin/bash
 */
bool delete_temp_file(std::string s);

/**
 * Deletes a collection of temporary files.
 * The files will only be deleted if a prefix of s was previously returned by
 * get_temp_name(). This is done for safety to prevent this function from being
 * used to delete arbitrary files.
 *
 * For instance, if get_temp_name() previously returned /tmp/file51apTO ,
 * delete_temp_files will succeed on a collection of files
 * {/tmp/file51apTO.csv, /tmp/file51apTO.txt}. delete_temp_file will
 * fail on stuff like /usr/bin/bash
 */
void delete_temp_files(std::vector<std::string> files);


/**
 * Deletes all temporary directories in the temporary graphlab/ directory 
 * (/var/tmp/graphlab) which are no longer used. i.e. was created by a process
 * which no longer exists.
 */
void reap_unused_temp_files();

/**
 * Deletes all temp files created by the current process
 */
void reap_current_process_temp_files();

/**
 * Returns the set of temp directories
 */
std::vector<std::string> get_temp_directories();

/**
 * Returns the number of temp directories
 */
size_t num_temp_directories();
} // namespace graphlab
#endif

/*
*
* LibAnt - A handy C++ library
* Copyright (C) 2021 Antigloss Huang (https://github.com/antigloss) All rights reserved.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef LIBANT_FILE_UTILS_FILE_PURGER_H_
#define LIBANT_FILE_UTILS_FILE_PURGER_H_

#include <condition_variable>
#include <filesystem>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

namespace ant {

/**
 * Monitor specified directories and purge old files under those directories according to the associated rules.
 */
class FilePurger {
public:
    /**
     * Purging rule
     */
    class PurgingRule {
    public:
        friend class FilePurger;

    public:
        /**
         * Construct a purging rule
         *
         * @param inactiveTime Purge files whose last modified time are at least `InactiveTime` seconds ago.
         * @param recursive Whether to purge directory recursively.
         * @param purgeEmptyDir Whether to purge empty directory.
         */
        PurgingRule(time_t inactiveTime, bool recursive = true, bool purgeEmptyDir = true)
            : inactiveTime_(inactiveTime)
            , purgeRecursively_(recursive)
            , purgeEmptyDirectory_(purgeEmptyDir)
        {
        }

    private:
        time_t inactiveTime_;
        bool purgeRecursively_;
        bool purgeEmptyDirectory_;
    };

public:
    /**
     * Construct a FilePurger object and start a thread to purge old files.
     */
    FilePurger(const std::unordered_map<std::string, PurgingRule>* rules = nullptr)
        : stop_(false)
        , purgingThread_(&FilePurger::run, this)
    {
        if (rules) {
            rules_ = *rules;
        }
    }

    ~FilePurger()
    {
        cvMtx_.lock();
        stop_ = true;
        cvMtx_.unlock();
        cv_.notify_one();

        purgingThread_.join();
    }

    /**
     * Add a directory to be monitored and purge old files under this directory according to the associated rule.
     *
     * @param dir
     * @param rule
     */
    void Add(std::string dir, const PurgingRule& rule)
    {
        rulesMtx_.lock();
        rules_.insert_or_assign(std::move(dir), rule);
        rulesMtx_.unlock();
    }

    /**
     * Remove a monitored directory
     *
     * @param dir
     */
    void Remove(const std::string& dir)
    {
        rulesMtx_.lock();
        rules_.erase(dir);
        rulesMtx_.unlock();
    }

    /**
     * Clear all monitored directories
     */
    void Clear()
    {
        rulesMtx_.lock();
        rules_.clear();
        rulesMtx_.unlock();
    }

private:
    void run();
    void purgeOldFiles(const std::filesystem::file_time_type& tNow, const std::string& dir, const PurgingRule& rule);

private:
    std::mutex cvMtx_;
    std::condition_variable cv_;
    bool stop_;

    std::thread purgingThread_;
    std::mutex rulesMtx_;
    // <dir, purging rule>
    std::unordered_map<std::string, PurgingRule> rules_;
};

} // namespace ant

#endif //LIBANT_FILE_UTILS_FILE_PURGER_H_

/**
 * @file event_handler.h
 * @brief Event dispatching interface.
 */

#pragma once

namespace event_handler
{
    /**
     * @brief Processes and dispatches a named system or user event.
     * @param[in] event Null-terminated event identifier string.
     */
    void handle_event(const char* event);
} // namespace event_handler
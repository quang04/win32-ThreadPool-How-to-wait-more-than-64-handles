# win32-ThreadPool-How-to-wait-more-than-64-handles
How to use thread pool in win32 and waiting more than 64 handles.

The program will create 3000 tasks and feed to the pool thread for execution. Then software will wait all a tasks for completion and continue main thread.

## Introduction
[According to Microsoft Documment](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitformultipleobjects), `WaitForMultipleObjects` can wait up to `MAXIMUM_WAIT_OBJECTS`(64). So the question is how to deal with more than 64 handles

This is illustration how to use thread pool in win32 and how deal with waiting more than 64 handles.

The idea for dealing more than 64 objects is inspired from [here](https://apps.dtic.mil/sti/pdfs/ADA626969.pdf).

The limitation of this idea is the maximum 4096 handles (64x64)

## Usage
The project is using vs2019, x64, c++20 and win32/mfc core



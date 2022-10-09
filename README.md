# win32-ThreadPool-How-to-wait-more-than-64-handles
how to use thread pool in win32 and wating more than 64 handles

## Introduction
This is illustration how to use thread pool in win32 and how deal with waiting more than 64 handles.

The idea for dealing more than 64 objects is inspired from [there]https://apps.dtic.mil/sti/pdfs/ADA626969.pdf
The limitation of this idea is the maximum is 4096 handles (64x64)

## Usage
The project is using vs2019, c++20 and win32/mfc core



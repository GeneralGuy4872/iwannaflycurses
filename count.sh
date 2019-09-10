#!/bin/sh
find  * -name "*.[ch]" | xargs wc -l > lines_of_c.log
find  * -name "*.awk" -o -name "*.pl" -o -name "*.cl" -o -name "*.scm" -o -name "*.icn" -o -name "*.sno" -o -name "*.lua" -o -name "*.py" -o -name "*.js" -o -name "*.sh" -o -name "make" | xargs wc -l > lines_of_script.log
find  * -name "*.xml" -o -name "*.json" -o -name "*.ini" -o -name "*.[tc]sv" -o -name "*.tab" -o -name "*.dat" | xargs wc -l > lines_of_data.log
find  * -name "*.hex" -o -name "*.r*" | xargs wc -c > bytes_of_binary.log
find  * -name "*.txt" -o -name "*.nfo" -o ! -name "*.*" -a ! -name "make" -a -type f | xargs wc -w > words_of_text.log
find  * -name "*.md" -o -name "*.html" | xargs wc -w > words_of_markup.log
find  * -name "*.man.[0-9]" -name "README" > lines_of_docs.log

@echo off
CALL commands\\bat\\board.bat

pio run -e %BOARDTYPE% && pio run -e %BOARDTYPE% -t buildfs
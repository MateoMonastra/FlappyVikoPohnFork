set positionDir=%1
set copyDir=%2
set pasteDir=%3

cd %positionDir%
mkdir res
xcopy /s /e /y %copyDir% %pasteDir%
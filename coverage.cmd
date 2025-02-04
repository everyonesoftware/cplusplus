call test.cmd

rmdir /S /Q outputs\coverage

mkdir outputs\coverage\html
grcov outputs --source-dir sources --binary-path outputs --branch --output-types html --output-path outputs\coverage\ > outputs\coverage\html\grcov.txt 2>&1

@REM mkdir outputs\coverage\lcov
@REM grcov outputs --source-dir sources --binary-path outputs --branch --output-types lcov --output-path outputs\coverage\lcov\lcov.info > outputs\coverage\lcov\grcov.txt 2>&1
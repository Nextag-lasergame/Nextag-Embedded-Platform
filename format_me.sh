files=$(git diff --name-only develop -- '*.cpp' '*.h' '*.c' '*.cc' '*.hpp' :^third-party :^*build*)

for file in $files
do
  clang-format -i --Werror "$file"
done
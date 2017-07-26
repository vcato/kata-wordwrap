#define _GLIBCXX_DEBUG 1

#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>

using std::string;
using std::cerr;


static size_t findSpaceAfter(const string &s,size_t position)
{
  return std::find(s.begin()+position,s.end(),' ') - s.begin();
}


static size_t findSpaceBefore(const string &s,size_t position)
{
  while (s[position]!=' ') {
    if (position==0) {
      return position;
    }
    --position;
  }

  return position;
}


static size_t findBreakPoint(const string &s,size_t line_length)
{
  size_t position = findSpaceBefore(s,line_length);

  if (position==0) {
    return findSpaceAfter(s,line_length);
  }

  while (s[position-1]==' ') {
    --position;
  }

  return position;
}


static string leftPart(const string &s,size_t end_position)
{
  return s.substr(0,end_position);
}


static string rightPart(const string &s,size_t begin_position)
{
  return s.substr(begin_position,s.npos);
}


static size_t findNextNonSpace(const string &s,size_t position)
{
  while (s[position]==' ') {
    ++position;
  }

  return position;
}


static string wordWrap(const string &s,size_t line_length)
{
  if (s.length()<=line_length) {
    return s;
  }

  size_t prev_end = findBreakPoint(s,line_length);
  size_t next_begin = findNextNonSpace(s,prev_end);

  if (prev_end==s.length()) {
    return s;
  }

  string left = leftPart(s,prev_end);
  string right = wordWrap(rightPart(s,next_begin),line_length);

  return left + "\n" + right;
}


static void test1()
{
  string words = "this is a test of word wrap";
  int line_length = 10;

  string expected_result =
    "this is a\n"
    "test of\n"
    "word wrap";

  string result = wordWrap(words,line_length);
  assert(result==expected_result);
}


static void test2()
{
  string words = "this";
  int line_length = 10;
  string expected_result = "this";

  string result = wordWrap(words,line_length);
  assert(result==expected_result);
}


static void test3()
{
  string words = "this is a";
  int line_length = 9;
  string expected_result = "this is a";

  string result = wordWrap(words,line_length);
  assert(result==expected_result);
}


static void test4()
{
  string words = "this is a test";
  int line_length = 9;
  string expected_result = "this is a\ntest";

  string result = wordWrap(words,line_length);
  assert(result==expected_result);
}


static void test5()
{
  string words = "this is another";
  int line_length = 9;
  string expected_result = "this is\nanother";

  string result = wordWrap(words,line_length);
  assert(result==expected_result);
}


static void test6()
{
  string words = "this is another";
  int line_length = 1;
  string expected_result = "this\nis\nanother";

  string result = wordWrap(words,line_length);
  assert(result==expected_result);
}


static void test7()
{
  string words = "this";
  int line_length = 1;
  string expected_result = "this";

  string result = wordWrap(words,line_length);
  assert(result==expected_result);
}


static void test8()
{
  string words = "";
  int line_length = 1;
  string expected_result = "";

  string result = wordWrap(words,line_length);
  assert(result==expected_result);
}


int main()
{
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
}

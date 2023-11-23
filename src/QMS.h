#pragma once

#include "Util.h"
#include "Quiz.h"
#include "Question.h"

class QMS {
public:
    static void Save(Quiz quiz, std::string _path);
    static std::pair<Quiz, int> Load(std::string path);
};
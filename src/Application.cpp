#include "Application.h"

std::string Application::dir = "";
Quiz Application::workingQuiz = Quiz();

void Application::PollCommand() {
    const int color = Console::GetColor();
    Console::SetColor(Console::BLUE);
    Console::Print(dir + "> ");
    RunCommand(Command::Parse(Console::Input()));
    Console::SetColor(color);
}

void Application::RunCommand(Command command) {
    Console::Reset();

    if (!CommandHandler::Verify(command)) {
        Err(CommandHandler::GetErr(), false);
        PollCommand();
        return;
    }

    CommandHandler::Run(command);
}

void Application::SuccessMsg(std::string msg) {
    Console::SetColor(Console::GREEN);
    Console::Print(msg);
    Console::Reset();
}



void Application::Start() {
    dir = "";
    Console::Clear();
    Console::SetColor(Console::CYAN);

    std::string title = "  Quiz Maker v" + std::string(VERSION) + "  ";
    std::string bar;
    for (int i = 0; i < title.length(); i++) {
        bar += "=";
    };
    Console::Print(bar + "\n");
    Console::Print(title + "\n");
    Console::Print(bar + "\n");
    Console::Reset();
    Console::Print("\n\nEnter 'help' for a list of commands.\n\n");

    PollCommand();
}

void Application::Help() {
    Console::SetColor(Console::GREEN);
    Console::Print("COMMANDS:\n");
    Console::Print("q / quit    : quit program\n");
    Console::Print("q! / quit!  : force quit program\n");
    Console::Print("v / version : show app version\n");
    Console::Print("root        : go to root directory\n");
    Console::Print("help        : display this help message\n");
    Console::Print("docs        : open documentation in browser\n");
    Console::Print("create      : create new quiz\n");
    Console::Print("rename      : rename quiz\n");
    Console::Print("addq        : add question\n");
    Console::Print("listq       : list all questions\n");
    Console::Print("editq       : edit a question\n");
    Console::Print("delq        : delete a question\n");
    Console::Print("take        : take quiz\n");
    Console::Print("clr         : clear screen\n");
    Console::Print("save        : save quiz to path\n");
    Console::Print("load        : load quiz from path\n");
    Console::Print("\n");
    Console::Reset();
    PollCommand();
}

void Application::HelpMore() {
    Console::SetColor(Console::GREEN);
    Console::Print("(may have to expand window to see table correctly)\n");
    Console::Print("-------------------------------------------------------------------------------------------------------------------------------\n");
    Console::Print("|     COMMAND     |          EXPLANATION          |     ARGUMENTS    |             ARGS EXPLANATION             |  DIRECTORY  |\n");
    Console::Print("|-----------------------------------------------------------------------------------------------------------------------------|\n");
    Console::Print("|     q / quit    |         quit program          |         -        |                    -                     |     any     |\n");
    Console::Print("|    q! / quit!   |       force quit program      |         -        |                    -                     |     any     |\n");
    Console::Print("|   v / version   |        show app version       |         -        |                    -                     |     any     |\n");
    Console::Print("|      root       |      go to root directory     |         -        |                    -                     |     any     |\n");
    Console::Print("|      help       |      display help message     |       -more      |       more detailed help msg (this)      |     any     |\n");
    Console::Print("|      docs       | open documentation in browser |         -        |                    -                     |     any     |\n");
    Console::Print("|     create      |        create new quiz        |         -        |                    -                     |     Root    |\n");
    Console::Print("|     rename      |          rename quiz          |         -        |                    -                     |     Quiz    |\n");
    Console::Print("|      addq       |          add question         |   -mc, -wr, -tf  |   multiple choice, written, true/false   |     Quiz    |\n");
    Console::Print("|     listq       |       list all questions      |       -more      |            more detailed list            |     Quiz    |\n");
    Console::Print("|     editq       |        edit a question        |    -q, -c, -a    |   edit question, choices, and/or answer  |     Quiz    |\n");
    Console::Print("|     delq        |       delete a question       |         -        |                    -                     |     Quiz    |\n");
    Console::Print("|      take       |           take quiz           |         -        |                    -                     |     Quiz    |\n");
    Console::Print("|      clr        |          clear screen         |         -        |                    -                     |     Root    |\n");
    Console::Print("|      save       |       save quiz to path       |         -        |                    -                     |     Quiz    |\n");
    Console::Print("|      load       |      load quiz from path      |         -        |                    -                     |     Root    |\n");
    Console::Print("|                 |                               |                  |                                          |             |\n");
    Console::Print("-------------------------------------------------------------------------------------------------------------------------------\n");
    Console::Print("Use 'docs' to see full documentation.\n\n");
    Console::Reset();
    PollCommand();
}

void Application::Docs() {
    Util::OpenLink("https://github.com/jopo86/QuizMaker/wiki/Documentation");
    SuccessMsg("Attempted to open link in browser. If it doesn't open, use this link:\n");
    Console::SetColor(Console::CYAN);
    Console::Print("https://github.com/jopo86/QuizMaker/wiki/Documentation\n\n");
    Console::Reset();
    PollCommand();
}

void Application::Version() {
    Console::Print("Quiz Maker v" + std::string(VERSION) + "\n\n");
    PollCommand();
}

void Application::CreateQuiz() {
    dir = "Quiz";
    Console::Reset();
    Console::Print("Enter quiz name: ");
    workingQuiz = Quiz(Console::Input());
    SuccessMsg("Created empty quiz '" + workingQuiz.getName() + "'.\n\n");
    PollCommand();
}

void Application::RenameQuiz() {
    Console::Print("Enter new quiz name:\n");
    std::string name = Console::Input();
    workingQuiz.setName(name);
    SuccessMsg("Quiz name set to '" + name + "'.\n\n");
    PollCommand();
}

void Application::AddQuestion() {
    Console::Reset();
    Console::Reset();
    Console::Print("Enter Question type ('mc' for multiple choice, 'wr' for written, 'tf' for true/false):\n");
    std::string type = Console::Input();
    if (Util::EqualsIgnoreCase(type, "mc")) {
        AddQuestionMC();
    }
    else if (Util::EqualsIgnoreCase(type, "wr")) {
        AddQuestionWR();
    }
    else if (Util::EqualsIgnoreCase(type, "tf")) {
        AddQuestionTF();
    }
    else {
        Err("unrecognized response: '" + type + "'. (aborted)", false);
    }
}

void Application::AddQuestionWR() {
    Question wq(Question::WRITTEN);
    Console::Print("Enter Question: \n");
    wq.setQuestion(Console::Input());
    Console::Print("Enter answer:\n");
    wq.setAnswer(Console::Input());
    workingQuiz.addQuestion(wq);
    SuccessMsg("Question created.\n\n");
    PollCommand();
}

void Application::AddQuestionMC() {
    Question mcq(Question::MULTIPLE_CHOICE);
    Console::Print("Enter Question: \n");
    mcq.setQuestion(Console::Input());
    Console::Print("Enter choices (enter '-' when finished):\n");
    std::string choice;
    while (choice != "-") {
        choice = Console::Input();
        if (choice != "-") {
            mcq.addChoice(choice);
        }
    }
    Console::Print("Enter correct choice:\n");
    std::string ans = Console::Input();
    if (!mcq.isChoice(ans)) {
        Err("answer '" + ans + "' not found in choices. (aborted)", false);
        dir = "Quiz";
        return;
    }
    mcq.setAnswer(ans);
    workingQuiz.addQuestion(mcq);
    SuccessMsg("Question created.\n\n");
    PollCommand();
}

void Application::AddQuestionTF() {
    Question tfq(Question::TRUE_FALSE);
    Console::Print("Enter Question: \n");
    tfq.setQuestion(Console::Input());
    Console::Print("Enter answer (T/F): ");
    const char ans = Util::ToLower(Console::Input()[0]);
    if (!(ans == 't' || ans == 'f')) {
        Err("response must start with T/t or F/f. (aborted)", false);
        return;
    }
    tfq.setAnswer({ ans });
    workingQuiz.addQuestion(tfq);
    SuccessMsg("Question created.\n\n");
    PollCommand();
}

void Application::ListQuestions(bool more) {
    Console::Reset();

    if (workingQuiz.getQuestions().size() == 0) {
        Console::Print("Quiz has no questions.\n\n");
        PollCommand();
        return;
    }

    Console::Print("\n");
    for (int i = 0; i < workingQuiz.getQuestions().size(); i++) {
        Console::Reset();
        Question q = workingQuiz.getQuestions()[i];
        int qNum = i + 1;
        Console::Print(std::to_string(qNum) + ") " + q.getQuestion() + "\n");

        if (more) {
            Console::SetColor(Console::CYAN);
            int _type = q.getType();
            std::string type;
            if (_type == Question::WRITTEN) type = "written";
            else if (_type == Question::MULTIPLE_CHOICE) type = "multiple choice";
            else if (_type == Question::TRUE_FALSE) type = "true/false";
            Console::Print("Type: " + type + "\n");
            if (_type == Question::MULTIPLE_CHOICE) {
                Console::Print("Choices: \n");
                for (int j = 0; j < q.getChoices().size(); j++) {
                    Console::Print(std::string(1, Util::NumToLetter(j)) + ") " + q.getChoices()[j] + "\n");
                }
            }
            Console::Print("Answer: " + q.getAnswer() + "\n\n");
        }
    }
    if (!more) Console::Print("\n");
    PollCommand();
}

void Application::EditQuestion(bool q, bool c, bool a, int qNum) {
    Console::Reset();

    if (workingQuiz.getQuestions().size() == 0) {
        Console::Print("Quiz has no questions.\n\n");
        PollCommand();
        return;
    }

    if (qNum == -1) {
        Console::Print("Question # to edit (use 'listq' to see question #s): ");
        std::string response = Console::Input();
        if (response == "" || !Util::IsNumber(response)) {
            Err("'" + response + "' is not a number. (aborted)", false);
            return;
        }
        qNum = std::stoi(response);
    }
    size_t size = workingQuiz.getQuestions().size();
    if (qNum > size) {
        Err("too large, quiz only has " + std::to_string(size) + " questions. (aborted)", false);
        return;
    }

    Question oldQuestion = workingQuiz.getQuestions()[qNum - 1];
    if (oldQuestion.getType() != Question::MULTIPLE_CHOICE && c) {
        Err("requested to edit choices, but question is not multiple choice. (aborted)", false);
        return;
    }

    if (!q && !c && !a) {
        bool _q, _c, _a = false;

        Console::Print("\nEdit question? (y/n): ");
        if (Console::Input()[0] == 'y') _q = true;

        if (oldQuestion.getType() == Question::MULTIPLE_CHOICE) {
            Console::Print("Edit choices? (y/n): ");
            if (Console::Input()[0] == 'y') _c = true;
        }

        Console::Print("Edit answer? (y/n): ");
        if (Console::Input()[0] == 'y') _a = true;

        if (!_q && !_c && !_a) {
            Console::Print("\n");
            PollCommand();
            return;
        }
        EditQuestion(_q, _c, _a, qNum);
    }
    else {
        // create new quiz, add questions before current qNum
        Quiz newQuiz;
        newQuiz.setName(workingQuiz.getName());
        for (int i = 0; i < qNum - 1; i++) {
            newQuiz.addQuestion(workingQuiz.getQuestions()[i]);
        }

        // create new question to replace current qNum
        Question newQuestion(workingQuiz.getQuestions()[qNum - 1].getType());

        if (q) {
            Console::Print("\nOld question: ");
            Console::SetColor(Console::CYAN);
            Console::Print(oldQuestion.getQuestion());
            Console::Reset();
            Console::Print("\nEnter new question: ");
            newQuestion.setQuestion(Console::Input());
            SuccessMsg("Question updated.\n");
        }
        else newQuestion.setQuestion(oldQuestion.getQuestion());

        if (c) {
            Console::Print("\nOld choices: \n");
            Console::SetColor(Console::CYAN);
            for (int j = 0; j < oldQuestion.getChoices().size(); j++) {
                Console::Print(std::string(1, Util::NumToLetter(j)) + ") " + oldQuestion.getChoices()[j] + "\n");
            }
            Console::Reset();
            Console::Print("Enter new choices (type '-' when done): \n");
            std::string choice;
            while (choice != "-") {
                choice = Console::Input();
                if (choice != "-") {
                    newQuestion.addChoice(choice);
                }
            }
            SuccessMsg("Choices updated.\n");
        }
        else if (oldQuestion.getType() == Question::MULTIPLE_CHOICE) {
            newQuestion.setChoices(oldQuestion.getChoices());
        }

        if (a) {
            Console::Print("\nOld answer: ");
            Console::SetColor(Console::CYAN);
            Console::Print(oldQuestion.getAnswer());
            Console::Reset();
            Console::Print("\nEnter new answer: ");
            newQuestion.setAnswer(Console::Input());
            SuccessMsg("Answer updated.\n");
        }
        else newQuestion.setAnswer(oldQuestion.getAnswer());

        // add new question
        newQuiz.addQuestion(newQuestion);

        // add the rest of the questions
        for (int i = qNum; i < size; i++) {
            newQuiz.addQuestion(workingQuiz.getQuestions()[i]);
        }
        workingQuiz = newQuiz;

        Console::Print("\n");
        PollCommand();
    }
}

void Application::DeleteQuestion() {
    Console::Reset();

    if (workingQuiz.getQuestions().size() == 0) {
        Console::Print("Quiz has no questions.\n\n");
        PollCommand();
        return;
    }

    Console::Print("Question # to delete (use 'listq' to see question #s): ");
    std::string response = Console::Input();
    if (response == "" || !Util::IsNumber(response)) {
        Err("'" + response + "' is not a number. (aborted)", false);
        return;
    }
    int qNum = std::stoi(response);

    size_t size = workingQuiz.getQuestions().size();
    if (qNum > size) {
        Err("too large, quiz only has " + std::to_string(size) + " questions. (aborted)", false);
        return;
    }

    std::vector<Question> oldQuestions = workingQuiz.getQuestions();
    std::vector<Question> newQuestions;
    for (int i = 0; i < size; i++) {
        if (i != qNum - 1) newQuestions.push_back(oldQuestions[i]);
    }
    workingQuiz.setQuestions(newQuestions);
    SuccessMsg("Deleted question #" + std::to_string(qNum) + ".\n\n");
    PollCommand();
}

void Application::TakeQuiz() {
    Console::Reset();

    if (workingQuiz.getQuestions().size() == 0) {
        Console::Print("Quiz has no questions.\n\n");
        PollCommand();
        return;
    }

    std::string header = " TAKING QUIZ: '" + workingQuiz.getName() + "' ";
    Console::SetColor(Console::BLUE);
    Console::Print("\n" + header + "\n");
    Console::Reset();
    for (int i = 0; i < header.length(); i++) {
        Console::Print("-");
    }
    Console::Print("\n\n");

    int qNum = 1;
    int score = 0;
    int maxScore = workingQuiz.getQuestions().size();

    for (int i = 0; i < workingQuiz.getQuestions().size(); i++) {
        Question q = workingQuiz.getQuestions()[i];
        Console::SetColor(Console::MAGENTA);
        Console::Print("QUESTION " + std::to_string(qNum) + ":\n");
        Console::SetColor(Console::CYAN);
        Console::Print(q.getQuestion() + "\n\n");
        Console::Reset();
        if (q.getType() == Question::WRITTEN) {
            Console::Print("Enter answer: ");
            std::string answer = Console::Input();
            if (q.check(answer)) {
                Console::SetColor(Console::GREEN);
                Console::Print("Correct!\n\n");
                Console::Reset();
                score++;
            }
            else {
                Console::SetColor(Console::RED);
                Console::Print("Incorrect!\n\n");
                Console::Reset();
            }
        }

        else if (q.getType() == Question::MULTIPLE_CHOICE) {
            Console::Print("Choices:\n");
            Console::SetColor(Console::CYAN);
            for (int j = 0; j < q.getChoices().size(); j++) {
                Console::Print(std::string(1, Util::NumToLetter(j)) + ") " + q.getChoices()[j] + "\n");
            }
            Console::Reset();
            Console::Print("Enter (letter) choice: ");
            char letterChoice = Console::Input()[0];
            int numChoice = Util::LetterToNum(letterChoice);
            if (numChoice >= q.getChoices().size() || numChoice == -1) {
                Err("choice does not exist. (aborted)", false);
                PollCommand();
                return;
            }
            if (q.check(q.getChoices()[numChoice])) {
                Console::SetColor(Console::GREEN);
                Console::Print("Correct!\n\n");
                Console::Reset();
                score++;
            }
            else {
                Console::SetColor(Console::RED);
                Console::Print("Incorrect!\n\n");
                Console::Reset();
            }
        }

        else if (q.getType() == Question::TRUE_FALSE) {
            Console::Print("Enter answer (T/F): ");
            char ans = Util::ToLower(Console::Input()[0]);
            if (q.check({ ans })) {
                Console::SetColor(Console::GREEN);
                Console::Print("Correct!\n\n");
                Console::Reset();
                score++;
            }
            else {
                Console::SetColor(Console::RED);
                Console::Print("Incorrect!\n\n");
                Console::Reset();
            }
        }
        qNum++;
    }

    SuccessMsg("Quiz Finished. Score: " + std::to_string(score) + "/" + std::to_string(maxScore) + " (" + std::to_string((int)((float)score / maxScore * 100)) + "%)" + "\n\n");
    PollCommand();
}

void Application::SaveQuiz() {
    Console::Print("Enter path to save quiz to (relative to location of QuizMaker.exe, or absolute):\n");
    std::string path = Console::Input();
    QMS::Save(workingQuiz, path);
    SuccessMsg("Quiz saved to '" + path + "'.\n\n");
    PollCommand();
}

void Application::LoadQuiz() {
    Console::Print("Enter path to load quiz from (relative to location of QuizMaker.exe, or absolute):\n");
    std::string path = Console::Input();
    std::pair<Quiz, int> loadpair = QMS::Load(path);
    if (loadpair.second == QMS::FILE_NOT_QMS) {
        Err("not a .qms file\n\n", false);
        PollCommand();
        return;
    }
    else if (loadpair.second == QMS::FILE_NOT_FOUND) {
        Err("path '" + path + "' not found. (aborted)", false);
        PollCommand();
        return;
    }
    workingQuiz = loadpair.first;
    dir = "Quiz";
    SuccessMsg("Quiz loaded from '" + path + "'.\n\n");
    PollCommand();
}

void Application::Root() {
    Console::Print("Are you sure you want to go back to root directory? Progress may be lost. (y/n): ");
    std::string response = Console::Input();
    if (response == "y") {
        workingQuiz = Quiz();
        dir = "";
        Console::Print("\n");
        PollCommand();
    }
    else if (response == "n") {
        Console::Print("\n");
        PollCommand();
    }
    else {
        Err("unhandled response '" + response, false);
        PollCommand();
    }
}

void Application::Clr() {
    Console::Clear();
    PollCommand();
}

void Application::Err(std::string msg, bool fatal) {
    Console::SetColor(Console::RED);
    if (fatal) {
        Console::Print("FATAL ERROR: " + msg + "\n\n[Enter] to quit");
        Console::Input();
        exit(0);
    }
    else {
        Console::Print("ERROR: " + msg + "\n\n");
        PollCommand();
    }
}

void Application::Quit() {
    Console::Reset();
    Console::Print("Are you sure you want to quit? Progress may be lost. (y/n): ");
    std::string response = Console::Input();
    if (response == "y") {
        ForceQuit();
    }
    else if (response == "n") {
        Console::Print("\n");
        PollCommand();
    }
    else {
        Err("unhandled response '" + response + "'\n\n", false);
        PollCommand();
    }
}

void Application::ForceQuit() {
    exit(0);
}

std::string Application::GetDir() {
    return dir;
}
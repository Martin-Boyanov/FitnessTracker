#ifndef THEORYCOURSE_H
#define THEORYCOURSE_H

#include <string>
#include <vector>

using namespace std;

class TheoryLesson {
private:
    string title;
    string content;

public:
    TheoryLesson(const string& title, const string& content);

    string getTitle() const;
    string getContent() const;
    void showLesson() const;
};

class QuizQuestion {
private:
    string questionText;
    vector<string> answers;
    int correctAnswerIndex;
    string explanation;

public:
    QuizQuestion(
        const string& questionText,
        const vector<string>& answers,
        int correctAnswerIndex,
        const string& explanation
    );

    void showQuestion() const;
    bool checkAnswer(int userAnswerIndex) const;
    void showExplanation() const;
    int getAnswersCount() const;
};

class QuizResult {
private:
    string courseTitle;
    int correctAnswers;
    int totalQuestions;
    bool passed;

public:
    QuizResult(
        const string& courseTitle,
        int correctAnswers,
        int totalQuestions,
        bool passed
    );

    double getScorePercent() const;
    bool hasPassed() const;
    void showResult() const;
};

class FitnessQuiz {
private:
    vector<QuizQuestion> questions;
    int passingScore;

public:
    FitnessQuiz(int passingScore);

    void addQuestion(const QuizQuestion& question);
    QuizResult startQuiz(const string& courseTitle) const;
};

class TheoryCourse {
private:
    string title;
    vector<TheoryLesson> lessons;
    FitnessQuiz quiz;

public:
    TheoryCourse(const string& title, const FitnessQuiz& quiz);

    void addLesson(const TheoryLesson& lesson);
    void startCourse() const;
    QuizResult startQuiz() const;
};

#endif
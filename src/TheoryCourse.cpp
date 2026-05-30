#include "../include/TheoryCourse.h"
#include <iostream>
#include <limits>

using namespace std;

TheoryLesson::TheoryLesson(const string& title, const string& content) {
    this->title = title;
    this->content = content;
}

string TheoryLesson::getTitle() const {
    return title;
}

string TheoryLesson::getContent() const {
    return content;
}

void TheoryLesson::showLesson() const {
    cout << "\n===== Lesson: " << title << " =====\n";
    cout << content << endl;
}

QuizQuestion::QuizQuestion(
    const string& questionText,
    const vector<string>& answers,
    int correctAnswerIndex,
    const string& explanation
) {
    this->questionText = questionText;
    this->answers = answers;
    this->correctAnswerIndex = correctAnswerIndex;
    this->explanation = explanation;
}

void QuizQuestion::showQuestion() const {
    cout << "\n" << questionText << endl;

    for (int i = 0; i < (int)answers.size(); i++) {
        cout << i + 1 << ". " << answers[i] << endl;
    }
}

bool QuizQuestion::checkAnswer(int userAnswerIndex) const {
    return userAnswerIndex == correctAnswerIndex;
}

void QuizQuestion::showExplanation() const {
    cout << "Explanation: " << explanation << endl;
}

int QuizQuestion::getAnswersCount() const {
    return (int)answers.size();
}

QuizResult::QuizResult(
    const string& courseTitle,
    int correctAnswers,
    int totalQuestions,
    bool passed
) {
    this->courseTitle = courseTitle;
    this->correctAnswers = correctAnswers;
    this->totalQuestions = totalQuestions;
    this->passed = passed;
}

double QuizResult::getScorePercent() const {
    if (totalQuestions == 0) {
        return 0;
    }

    return (correctAnswers * 100.0) / totalQuestions;
}

bool QuizResult::hasPassed() const {
    return passed;
}

void QuizResult::showResult() const {
    cout << "\n===== Quiz Result =====\n";
    cout << "Course: " << courseTitle << endl;
    cout << "Correct answers: " << correctAnswers << "/" << totalQuestions << endl;
    cout << "Score: " << getScorePercent() << "%" << endl;

    if (passed) {
        cout << "Status: Passed\n";
        cout << "You have enough basic knowledge to start building simple workout ideas.\n";
    } else {
        cout << "Status: Not passed\n";
        cout << "Review the lessons and try again before building your own workout plan.\n";
    }
}

FitnessQuiz::FitnessQuiz(int passingScore) {
    this->passingScore = passingScore;
}

void FitnessQuiz::addQuestion(const QuizQuestion& question) {
    questions.push_back(question);
}

QuizResult FitnessQuiz::startQuiz(const string& courseTitle) const {
    int correctAnswers = 0;

    cout << "\n===== Fitness Theory Quiz =====\n";
    cout << "Answer the questions using the number of the correct answer.\n";
    cout << "Passing score: " << passingScore << "/" << questions.size() << endl;

    for (int i = 0; i < (int)questions.size(); i++) {
        questions[i].showQuestion();

        int answer;

        while (true) {
            cout << "Your answer: ";
            cin >> answer;

            if (!cin.fail() && answer >= 1 && answer <= questions[i].getAnswersCount()) {
                break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid answer. Try again.\n";
        }

        int answerIndex = answer - 1;

        if (questions[i].checkAnswer(answerIndex)) {
            cout << "Correct.\n";
            correctAnswers++;
        } else {
            cout << "Wrong.\n";
        }

        questions[i].showExplanation();
    }

    bool passed = correctAnswers >= passingScore;

    return QuizResult(
        courseTitle,
        correctAnswers,
        (int)questions.size(),
        passed
    );
}

TheoryCourse::TheoryCourse(const string& title, const FitnessQuiz& quiz)
    : quiz(quiz) {
    this->title = title;
}

void TheoryCourse::addLesson(const TheoryLesson& lesson) {
    lessons.push_back(lesson);
}

void TheoryCourse::startCourse() const {
    cout << "\n===== Mini Fitness Theory Course =====\n";
    cout << "Course: " << title << endl;
    cout << "Goal: learn how exercises connect to muscles and how to build basic workout logic.\n";

    for (const TheoryLesson& lesson : lessons) {
        lesson.showLesson();
    }

    cout << "\nCourse lessons finished. You can now start the quiz.\n";
}

QuizResult TheoryCourse::startQuiz() const {
    return quiz.startQuiz(title);
}
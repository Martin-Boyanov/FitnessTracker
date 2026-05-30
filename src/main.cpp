#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <string>
#include <ctime>
#include <sstream>
#include "../include/UserProfile.h"
#include "../include/Exercise.h"
#include "../include/Workout.h"
#include "../include/Calculator.h"
#include "../include/WorkoutPlan.h"
#include "../include/Challenge.h"
#include "../include/PersonalRecord.h"
#include "../include/TheoryCourse.h"
#include "../include/ReportExporter.h"
#include "../include/CustomWorkoutBuilder.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readIntInRange(const string& message, int minValue, int maxValue) {
    int value;

    while (true) {
        cout << message;
        cin >> value;

        if (!cin.fail() && value >= minValue && value <= maxValue) {
            return value;
        }

        clearInput();
        cout << "Invalid input. Enter a value between "
             << minValue << " and " << maxValue << ".\n";
    }
}

double readDoubleInRange(const string& message, double minValue, double maxValue) {
    double value;

    while (true) {
        cout << message;
        cin >> value;

        if (!cin.fail() && value >= minValue && value <= maxValue) {
            return value;
        }

        clearInput();
        cout << "Invalid input. Enter a value between "
             << minValue << " and " << maxValue << ".\n";
    }
}

string getTodayDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    stringstream ss;
    ss << localTime->tm_mday << "."
       << localTime->tm_mon + 1 << "."
       << localTime->tm_year + 1900;

    return ss.str();
}

string chooseGender() {
    cout << "\nChoose gender:\n";
    cout << "1. Male\n";
    cout << "2. Female\n";

    int choice = readIntInRange("Choose option: ", 1, 2);

    if (choice == 1) {
        return "Male";
    }

    return "Female";
}

string chooseActivityLevel() {
    cout << "\nChoose activity level:\n";
    cout << "1. Low - little or no training\n";
    cout << "2. Light - 1-3 workouts per week\n";
    cout << "3. Moderate - 3-5 workouts per week\n";
    cout << "4. High - 6+ workouts per week\n";

    int choice = readIntInRange("Choose option: ", 1, 4);

    if (choice == 1) {
        return "Low";
    }

    if (choice == 2) {
        return "Light";
    }

    if (choice == 3) {
        return "Moderate";
    }

    return "High";
}

string chooseGoal() {
    cout << "\nChoose goal:\n";
    cout << "1. Lose fat\n";
    cout << "2. Maintain weight\n";
    cout << "3. Build muscle\n";

    int choice = readIntInRange("Choose option: ", 1, 3);

    if (choice == 1) {
        return "Lose fat";
    }

    if (choice == 2) {
        return "Maintain weight";
    }

    return "Build muscle";
}

UserProfile createUserProfile() {
    string name;

    cout << "===== Create User Profile =====\n";
    cout << "Enter your name: ";
    getline(cin, name);

    if (name.empty()) {
        name = "User";
    }

    string gender = chooseGender();
    int age = readIntInRange("Enter age: ", 10, 100);
    double heightCm = readDoubleInRange("Enter height in cm: ", 100, 250);
    double weightKg = readDoubleInRange("Enter weight in kg: ", 30, 300);
    string activityLevel = chooseActivityLevel();
    string goal = chooseGoal();

    cout << "\nProfile created successfully.\n";

    return UserProfile(
        name,
        age,
        gender,
        heightCm,
        weightKg,
        activityLevel,
        goal
    );
}

vector<Exercise*> createExerciseDatabase() {
    vector<Exercise*> exercises;

    exercises.push_back(new StrengthExercise(
        "Squat",
        "Legs and glutes",
        "Barbell",
        "Medium",
        "The squat mainly trains the quadriceps, gluteus maximus, hamstrings and core stabilizers.",
        4,
        8
    ));

    exercises.push_back(new StrengthExercise(
        "Bench Press",
        "Chest, shoulders and triceps",
        "Barbell",
        "Medium",
        "The bench press mainly trains the chest, front deltoids and triceps.",
        4,
        8
    ));

    exercises.push_back(new StrengthExercise(
        "Dumbbell Row",
        "Back and biceps",
        "Dumbbells",
        "Medium",
        "The dumbbell row trains the lats, upper back, rear deltoids and biceps.",
        4,
        10
    ));

    exercises.push_back(new StrengthExercise(
        "Dumbbell Shoulder Press",
        "Shoulders and triceps",
        "Dumbbells",
        "Medium",
        "The dumbbell shoulder press trains the front and side deltoids and also uses the triceps.",
        3,
        10
    ));

    exercises.push_back(new BodyweightExercise(
        "Push-up",
        "Chest, shoulders and triceps",
        "Bodyweight",
        "Easy",
        "Push-ups train the chest, shoulders, triceps and core stability.",
        1
    ));

    exercises.push_back(new BodyweightExercise(
        "Pull-up",
        "Back and biceps",
        "Bodyweight",
        "Hard",
        "Pull-ups train the lats, upper back, biceps and grip strength.",
        3
    ));

    exercises.push_back(new BodyweightExercise(
        "Plank",
        "Core",
        "Bodyweight",
        "Easy",
        "The plank trains core stability, abs, lower back and shoulder endurance.",
        1
    ));

    exercises.push_back(new CardioExercise(
        "Running",
        "Cardiovascular system and legs",
        "None",
        "Medium",
        "Running improves endurance and trains the heart, lungs and leg muscles.",
        "Moderate"
    ));

    return exercises;
}

TheoryCourse createTheoryCourse() {
    FitnessQuiz quiz(10);

    quiz.addQuestion(QuizQuestion(
        "What is the main goal of a good workout plan?",
        {
            "To randomly use many exercises",
            "To match exercises, volume and difficulty to the user's goal",
            "To train only one muscle forever",
            "To avoid progress"
        },
        1,
        "A good workout plan should match the user's goal, recovery, equipment and training level."
    ));

    quiz.addQuestion(QuizQuestion(
        "Which muscles does the squat mainly train?",
        {
            "Chest and triceps",
            "Quadriceps, glutes, hamstrings and core",
            "Biceps only",
            "Shoulders only"
        },
        1,
        "The squat is a lower-body compound movement. It trains quadriceps, glutes, hamstrings and core stabilizers."
    ));

    quiz.addQuestion(QuizQuestion(
        "Which exercise is most suitable for chest development?",
        {
            "Bench Press",
            "Running",
            "Plank",
            "Dumbbell Row"
        },
        0,
        "Bench Press mainly trains the chest, front deltoids and triceps."
    ));

    quiz.addQuestion(QuizQuestion(
        "Which exercise mainly targets the back and biceps?",
        {
            "Dumbbell Row",
            "Bench Press",
            "Push-up",
            "Running"
        },
        0,
        "Dumbbell Row trains the lats, upper back, rear deltoids and biceps."
    ));

    quiz.addQuestion(QuizQuestion(
        "What is progressive overload?",
        {
            "Changing exercises randomly every day",
            "Slowly increasing difficulty over time",
            "Training only once per month",
            "Avoiding hard sets"
        },
        1,
        "Progressive overload means gradually increasing weight, reps, sets, time or difficulty so the body adapts."
    ));

    quiz.addQuestion(QuizQuestion(
        "Why is the shoulder often trained with more than one movement?",
        {
            "Because it has different parts that work at different angles",
            "Because shoulders do not need recovery",
            "Because one exercise trains the entire body",
            "Because cardio is not useful"
        },
        0,
        "The shoulder has different heads. Different angles emphasize different parts of the shoulder."
    ));

    quiz.addQuestion(QuizQuestion(
        "Which exercise is best measured by time instead of reps?",
        {
            "Push-up",
            "Pull-up",
            "Plank",
            "Bench Press"
        },
        2,
        "Plank is an isometric exercise, so it is usually measured by hold time."
    ));

    quiz.addQuestion(QuizQuestion(
        "What does workout volume usually mean in this project?",
        {
            "Calories burned",
            "Reps x weight",
            "Body fat percentage",
            "Heart rate"
        },
        1,
        "In this project, training volume means total lifted weight: reps x weight."
    ));

    quiz.addQuestion(QuizQuestion(
        "If your goal is muscle gain, what is usually a good training direction?",
        {
            "Moderate reps, enough sets and progressive overload",
            "Never increasing difficulty",
            "Only cardio",
            "No recovery"
        },
        0,
        "Muscle gain usually needs enough training volume, progressive overload, good form and recovery."
    ));

    quiz.addQuestion(QuizQuestion(
        "If you only have bodyweight equipment, what should your plan use?",
        {
            "Only barbell exercises",
            "Exercises like push-ups, pull-ups, plank and running",
            "No training at all",
            "Only machine exercises"
        },
        1,
        "A realistic workout plan must match the equipment the user actually has."
    ));

    quiz.addQuestion(QuizQuestion(
        "Why should personal records be compared to your own previous results?",
        {
            "Because progress is individual",
            "Because everyone has the same body",
            "Because form does not matter",
            "Because records should never change"
        },
        0,
        "Your own previous results are the most useful comparison because progress depends on the person."
    ));

    quiz.addQuestion(QuizQuestion(
        "What is the main role of recovery?",
        {
            "It gives the body time to adapt after training",
            "It makes training useless",
            "It replaces workouts",
            "It means never training again"
        },
        0,
        "Training creates stimulus, but recovery allows the body to adapt and improve."
    ));

    quiz.addQuestion(QuizQuestion(
        "Which combination is best for a balanced simple workout?",
        {
            "Only biceps every day",
            "Push, pull, legs/core movements",
            "Only running",
            "Only plank"
        },
        1,
        "A balanced plan usually includes pushing, pulling, lower-body and core work."
    ));

    quiz.addQuestion(QuizQuestion(
        "Why should exercise choice depend on the user's goal?",
        {
            "Because different goals need different training focus",
            "Because goals do not matter",
            "Because all exercises have the same effect",
            "Because the user should never choose"
        },
        0,
        "Fat loss, muscle gain and maintenance can use different volume, reps, intensity and exercise choices."
    ));

    quiz.addQuestion(QuizQuestion(
        "When building your own workout, what should you be able to explain?",
        {
            "Why each exercise is included",
            "Nothing",
            "Only the color of the equipment",
            "Only the date"
        },
        0,
        "If you understand why an exercise is included, you are starting to think like your own coach."
    ));

    TheoryCourse course("Build Your Own Basic Workout", quiz);

    course.addLesson(TheoryLesson(
        "Lesson 1: What a workout plan actually is",
        "A workout plan is not just a random list of exercises. It is a structured decision: which muscles you want to train, what goal you have, how hard the session should be, and what equipment you can use. A good plan should have a reason behind every exercise."
    ));

    course.addLesson(TheoryLesson(
        "Lesson 2: Movement patterns",
        "A simple workout can be built from movement patterns: push, pull, legs and core. Push exercises include Bench Press and Push-up. Pull exercises include Pull-up and Dumbbell Row. Leg exercises include Squat. Core exercises include Plank."
    ));

    course.addLesson(TheoryLesson(
        "Lesson 3: Compound exercises",
        "Compound exercises train more than one muscle group at the same time. Squat, Bench Press, Pull-up and Dumbbell Row are compound movements. They are useful because they give a lot of training effect with fewer exercises."
    ));

    course.addLesson(TheoryLesson(
        "Lesson 4: Muscle groups and exercise choice",
        "A good workout should match exercises to the muscles you want to train. Bench Press trains chest, shoulders and triceps. Squat trains legs and glutes. Rows and pull-ups train back and biceps. Plank trains core stability."
    ));

    course.addLesson(TheoryLesson(
        "Lesson 5: Sets, reps and time",
        "Strength exercises are often measured in sets, reps and weight. Bodyweight exercises like push-ups and pull-ups can be measured in reps. Plank is different because it is an isometric hold, so it is better measured in seconds."
    ));

    course.addLesson(TheoryLesson(
        "Lesson 6: Progressive overload",
        "To improve, the body needs a reason to adapt. This can happen by slowly increasing weight, reps, sets, time, or exercise difficulty. The goal is not random hard training, but controlled progress."
    ));

    course.addLesson(TheoryLesson(
        "Lesson 7: Matching training to goals",
        "For muscle gain, a workout usually needs enough sets, moderate reps and progressive overload. For fat loss, training should be consistent and combined with calorie control. For maintenance, a balanced plan is usually enough."
    ));

    course.addLesson(TheoryLesson(
        "Lesson 8: Equipment-based planning",
        "A plan must match the available equipment. If you are in a full gym, you can use barbells and dumbbells. If you are travelling, bodyweight exercises are more realistic. A plan that cannot be performed is not a good plan."
    ));

    course.addLesson(TheoryLesson(
        "Lesson 9: Recovery and progression",
        "More training is not always better. The body needs recovery to adapt. A good beginner plan should be challenging, but not impossible. Progress should be gradual, measurable and safe."
    ));

    course.addLesson(TheoryLesson(
        "Lesson 10: Thinking like your own coach",
        "To build your own workout, you should be able to explain why each exercise is included. Example: Push-up is included for chest, shoulders and triceps. Pull-up is included for back and biceps. Squat is included for legs and glutes."
    ));

    return course;
}

void showExerciseDatabase(const vector<Exercise*>& exercises) {
    cout << "\n===== Exercise Database =====\n";

    for (int i = 0; i < (int)exercises.size(); i++) {
        cout << "\n-------------------------\n";
        cout << i + 1 << ". " << exercises[i]->getName() << endl;
        cout << exercises[i]->getDetails();
        cout << "Progression: " << exercises[i]->getProgressionInfo() << endl;
    }
}

double getStrengthMultiplier(const UserProfile& user) {
    if (user.getActivityLevel() == "Low") {
        return 0.45;
    }

    if (user.getActivityLevel() == "Light") {
        return 0.55;
    }

    if (user.getActivityLevel() == "Moderate") {
        return 0.70;
    }

    return 0.85;
}

int getRecommendedSets(const UserProfile& user) {
    if (user.getGoal() == "Build muscle") {
        return 4;
    }

    if (user.getGoal() == "Lose fat") {
        return 3;
    }

    return 3;
}

int getRecommendedReps(const UserProfile& user) {
    if (user.getGoal() == "Build muscle") {
        return 8;
    }

    if (user.getGoal() == "Lose fat") {
        return 12;
    }

    return 10;
}

int getWorkoutDuration(const UserProfile& user) {
    if (user.getActivityLevel() == "Low") {
        return 45;
    }

    if (user.getActivityLevel() == "Light") {
        return 55;
    }

    if (user.getActivityLevel() == "Moderate") {
        return 70;
    }

    return 85;
}

void showPersonalizedWorkout(const vector<Exercise*>& exercises, const UserProfile& user) {
    string todayDate = getTodayDate();

    int sets = getRecommendedSets(user);
    int reps = getRecommendedReps(user);
    int duration = getWorkoutDuration(user);

    double strengthMultiplier = getStrengthMultiplier(user);
    double bodyWeight = user.getWeightKg();

    double benchWeight = bodyWeight * strengthMultiplier;
    double squatWeight = bodyWeight * (strengthMultiplier + 0.20);

    WorkoutSession workout(
        todayDate,
        "Personalized workout based on your goal, weight and activity level",
        duration
    );

    ExerciseLog benchPressLog(exercises[1]);

    for (int i = 0; i < sets; i++) {
        benchPressLog.addSet(ExerciseSet(reps, benchWeight + i * 2.5));
    }

    ExerciseLog squatLog(exercises[0]);

    for (int i = 0; i < sets; i++) {
        squatLog.addSet(ExerciseSet(reps, squatWeight + i * 5));
    }

    workout.addExerciseLog(benchPressLog);
    workout.addExerciseLog(squatLog);

    cout << fixed << setprecision(2);
    cout << "\n===== Personalized Workout Plan =====\n";
    cout << "This workout is adapted to your profile data.\n";
    cout << "Date: " << todayDate << endl;
    cout << "Your goal: " << user.getGoal() << endl;
    cout << "Your activity level: " << user.getActivityLevel() << endl;
    cout << "Your body weight: " << user.getWeightKg() << " kg" << endl;

    cout << "\nHow the workout was adapted:\n";

    if (user.getGoal() == "Build muscle") {
        cout << "- Because your goal is muscle gain, the workout uses moderate reps and more sets.\n";
    } else if (user.getGoal() == "Lose fat") {
        cout << "- Because your goal is fat loss, the workout uses higher reps and slightly lower volume.\n";
    } else {
        cout << "- Because your goal is maintenance, the workout uses a balanced rep and set range.\n";
    }

    if (user.getActivityLevel() == "Low") {
        cout << "- Because your activity level is low, the starting weights and duration are conservative.\n";
    } else if (user.getActivityLevel() == "Light") {
        cout << "- Because your activity level is light, the workout stays beginner-friendly.\n";
    } else if (user.getActivityLevel() == "Moderate") {
        cout << "- Because your activity level is moderate, the workout uses a balanced difficulty.\n";
    } else {
        cout << "- Because your activity level is high, the workout uses a higher difficulty and longer duration.\n";
    }

    cout << "- The suggested weights are estimated from your body weight.\n";
    cout << "- This is not a perfect coach, but it gives a personalized starting point.\n";

    workout.showWorkout();
}

string chooseEquipmentType() {
    cout << "\nChoose available equipment:\n";
    cout << "1. Full gym\n";
    cout << "2. Dumbbells\n";
    cout << "3. Bodyweight only\n";
    cout << "4. Travel mode\n";

    int choice = readIntInRange("Choose option: ", 1, 4);

    if (choice == 1) {
        return "Full gym";
    }

    if (choice == 2) {
        return "Dumbbells";
    }

    if (choice == 3) {
        return "Bodyweight only";
    }

    return "Travel mode";
}

void generateWorkoutPlanByEquipment(const vector<Exercise*>& exercises) {
    string equipmentType = chooseEquipmentType();

    WorkoutPlan plan(
        "Adaptive Equipment-Based Plan",
        equipmentType
    );

    plan.generateByEquipment(exercises);
    plan.showPlan();
}

string getExerciseTypeName(Exercise* exercise) {
    if (dynamic_cast<StrengthExercise*>(exercise) != nullptr) {
        return "Strength";
    }

    if (dynamic_cast<BodyweightExercise*>(exercise) != nullptr) {
        return "Bodyweight";
    }

    if (dynamic_cast<CardioExercise*>(exercise) != nullptr) {
        return "Cardio";
    }

    return "Unknown";
}

string chooseReasonForExercise(Exercise* exercise) {
    cout << "\nWhy do you want to include " << exercise->getName() << "?\n";
    cout << "1. It targets the muscle group I want to train\n";
    cout << "2. It balances the workout movement pattern\n";
    cout << "3. It helps me progress toward a personal record\n";
    cout << "4. It fits my available equipment\n";
    cout << "5. Custom reason\n";

    int choice = readIntInRange("Choose option: ", 1, 5);

    if (choice == 1) {
        return "It targets " + exercise->getTargetMuscle() + ", which matches the goal of this workout.";
    }

    if (choice == 2) {
        return "It helps balance the workout by adding a different movement pattern.";
    }

    if (choice == 3) {
        return "It is included because the user wants measurable progress on this exercise.";
    }

    if (choice == 4) {
        return "It fits the available equipment: " + exercise->getEquipment() + ".";
    }

    clearInput();

    string reason;

    cout << "Enter your custom reason: ";
    getline(cin, reason);

    if (reason.empty()) {
        return "The user chose this exercise for a personal reason.";
    }

    return reason;
}

string createPrescriptionForExercise(Exercise* exercise) {
    if (dynamic_cast<StrengthExercise*>(exercise) != nullptr) {
        int sets = readIntInRange("Enter sets: ", 1, 10);
        int reps = readIntInRange("Enter reps per set: ", 1, 30);
        double weight = readDoubleInRange("Enter weight in kg: ", 1, 500);

        stringstream ss;
        ss << sets << " sets x " << reps << " reps x " << weight << " kg";
        return ss.str();
    }

    if (dynamic_cast<BodyweightExercise*>(exercise) != nullptr) {
        if (exercise->getName() == "Plank") {
            int sets = readIntInRange("Enter sets: ", 1, 10);
            int seconds = readIntInRange("Enter seconds per set: ", 5, 600);

            stringstream ss;
            ss << sets << " sets x " << seconds << " seconds";
            return ss.str();
        }

        int sets = readIntInRange("Enter sets: ", 1, 10);
        int reps = readIntInRange("Enter reps per set: ", 1, 200);

        stringstream ss;
        ss << sets << " sets x " << reps << " reps";
        return ss.str();
    }

    if (dynamic_cast<CardioExercise*>(exercise) != nullptr) {
        int minutes = readIntInRange("Enter duration in minutes: ", 1, 180);

        cout << "\nChoose intensity:\n";
        cout << "1. Low\n";
        cout << "2. Moderate\n";
        cout << "3. High\n";

        int intensityChoice = readIntInRange("Choose option: ", 1, 3);
        string intensity = "Low";

        if (intensityChoice == 2) {
            intensity = "Moderate";
        } else if (intensityChoice == 3) {
            intensity = "High";
        }

        stringstream ss;
        ss << minutes << " minutes at " << intensity << " intensity";
        return ss.str();
    }

    return "No prescription";
}

void buildCustomWorkoutAfterTheory(
    const vector<Exercise*>& exercises,
    bool theoryCoursePassed
) {
    if (!theoryCoursePassed) {
        cout << "\nThis feature is locked.\n";
        cout << "You must pass the mini theory course first.\n";
        cout << "The goal is to make sure you understand why exercises belong in a workout.\n";
        return;
    }

    clearInput();

    string workoutName;

    cout << "\n===== Build Your Own Workout =====\n";
    cout << "You unlocked this because you passed the theory course.\n";
    cout << "Enter workout name: ";
    getline(cin, workoutName);

    CustomWorkoutBuilder builder(workoutName);

    int exerciseCount = readIntInRange(
        "How many exercises do you want to add: ",
        1,
        8
    );

    for (int i = 0; i < exerciseCount; i++) {
        cout << "\n===== Choose Exercise " << i + 1 << " =====\n";

        for (int j = 0; j < (int)exercises.size(); j++) {
            cout << j + 1 << ". " << exercises[j]->getName()
                 << " | Target: " << exercises[j]->getTargetMuscle()
                 << " | Equipment: " << exercises[j]->getEquipment()
                 << endl;
        }

        int choice = readIntInRange(
            "Choose exercise: ",
            1,
            (int)exercises.size()
        );

        Exercise* selectedExercise = exercises[choice - 1];

        cout << "\nSelected: " << selectedExercise->getName() << endl;
        cout << "Theory reminder: " << selectedExercise->getTargetMuscle() << endl;
        cout << "Progression idea: " << selectedExercise->getProgressionInfo() << endl;

        string prescription = createPrescriptionForExercise(selectedExercise);
        string reason = chooseReasonForExercise(selectedExercise);

        builder.addExercise(CustomWorkoutExercise(
            selectedExercise->getName(),
            selectedExercise->getTargetMuscle(),
            getExerciseTypeName(selectedExercise),
            prescription,
            reason
        ));
    }

    builder.showWorkout();
}

void startFitnessChallenge(const vector<Exercise*>& exercises) {
    vector<int> challengeExerciseIndexes;

    cout << "\n===== Choose Challenge Exercise =====\n";

    for (int i = 0; i < (int)exercises.size(); i++) {
        if (dynamic_cast<BodyweightExercise*>(exercises[i]) != nullptr) {
            challengeExerciseIndexes.push_back(i);
            cout << challengeExerciseIndexes.size() << ". "
                 << exercises[i]->getName() << endl;
        }
    }

    if (challengeExerciseIndexes.empty()) {
        cout << "\nNo bodyweight exercises available for challenges.\n";
        return;
    }

    int choice = readIntInRange(
        "Choose exercise: ",
        1,
        (int)challengeExerciseIndexes.size()
    );

    int realExerciseIndex = challengeExerciseIndexes[choice - 1];
    Exercise* selectedExercise = exercises[realExerciseIndex];

    cout << "\nChoose challenge duration:\n";
    cout << "1. 15 days\n";
    cout << "2. 30 days\n";

    int durationChoice = readIntInRange("Choose option: ", 1, 2);
    int durationDays = durationChoice == 1 ? 15 : 30;

    bool isPlank = selectedExercise->getName() == "Plank";
    string unit = isPlank ? "seconds" : "reps";

    int dailyTarget;

    if (isPlank) {
        dailyTarget = readIntInRange("Enter daily target seconds: ", 5, 3600);
    } else {
        dailyTarget = readIntInRange("Enter daily target total reps: ", 1, 5000);
    }

    TrainingChallenge challenge(
        selectedExercise->getName() + " Challenge",
        durationDays,
        selectedExercise,
        dailyTarget,
        unit
    );

    challenge.showChallenge();

    int daysToLog = readIntInRange(
        "How many days do you want to log now: ",
        1,
        durationDays
    );

    for (int i = 0; i < daysToLog; i++) {
        cout << "\nDay " << challenge.getCurrentDay() << endl;

        int completedAmount;

        if (isPlank) {
            completedAmount = readIntInRange(
                "Enter completed total seconds today: ",
                0,
                10000
            );
        } else {
            completedAmount = readIntInRange(
                "Enter completed total reps today: ",
                0,
                10000
            );
        }

        challenge.updateDay(completedAmount);
    }

    challenge.showProgress();
}

void trackPersonalRecord(
    const vector<Exercise*>& exercises,
    RecordManager& manager,
    const UserProfile& user
) {
    vector<int> recordExerciseIndexes;

    cout << "\n===== Choose Exercise For Personal Record =====\n";

    for (int i = 0; i < (int)exercises.size(); i++) {
        bool isStrength = dynamic_cast<StrengthExercise*>(exercises[i]) != nullptr;
        bool isBodyweight = dynamic_cast<BodyweightExercise*>(exercises[i]) != nullptr;

        if (isStrength || isBodyweight) {
            recordExerciseIndexes.push_back(i);
            cout << recordExerciseIndexes.size() << ". "
                 << exercises[i]->getName() << endl;
        }
    }

    if (recordExerciseIndexes.empty()) {
        cout << "\nNo exercises available for personal records.\n";
        return;
    }

    int choice = readIntInRange(
        "Choose exercise: ",
        1,
        (int)recordExerciseIndexes.size()
    );

    int realExerciseIndex = recordExerciseIndexes[choice - 1];
    Exercise* selectedExercise = exercises[realExerciseIndex];

    string unit;
    double value;

    if (dynamic_cast<StrengthExercise*>(selectedExercise) != nullptr) {
        unit = "kg";
        value = readDoubleInRange("Enter your best lifted weight in kg: ", 1, 500);
    } else if (selectedExercise->getName() == "Plank") {
        unit = "seconds";
        value = readDoubleInRange("Enter your best plank time in seconds: ", 1, 10000);
    } else {
        unit = "reps";
        value = readDoubleInRange("Enter your best max reps in one set: ", 1, 10000);
    }

    manager.addOrUpdateRecord(
        selectedExercise->getName(),
        value,
        unit,
        user.getGender(),
        user.getWeightKg()
    );
}

bool startTheoryCourse() {
    TheoryCourse course = createTheoryCourse();

    course.startCourse();

    cout << "\nStart quiz now?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";

    int choice = readIntInRange("Choose option: ", 1, 2);

    if (choice == 1) {
        QuizResult result = course.startQuiz();
        result.showResult();

        if (result.hasPassed()) {
            cout << "\nYou passed the theory course.\n";
            cout << "You now understand enough to start building your own workout plan.\n";
            return true;
        }

        cout << "\nYou need to pass the quiz before building your own workout.\n";
        return false;
    }

    cout << "\nYou can come back to the theory course later.\n";
    return false;
}

void exportProgressReport(
    const UserProfile& user,
    const RecordManager& recordManager
) {
    clearInput();

    string fileName;

    cout << "\n===== Export Progress Report =====\n";
    cout << "Enter file name, for example fitness_report.txt: ";
    getline(cin, fileName);

    if (fileName.empty()) {
        fileName = "fitness_report.txt";
    }

    ReportExporter exporter(fileName);

    bool success = exporter.exportUserReport(user, recordManager);

    if (success) {
        cout << "\nReport exported successfully to: "
             << exporter.getFileName() << endl;
    } else {
        cout << "\nError: could not create report file.\n";
    }
}

void calculateOneRepMax(const vector<Exercise*>& exercises) {
    vector<int> strengthExerciseIndexes;

    cout << "\n===== Choose Strength Exercise =====\n";

    for (int i = 0; i < (int)exercises.size(); i++) {
        if (dynamic_cast<StrengthExercise*>(exercises[i]) != nullptr) {
            strengthExerciseIndexes.push_back(i);
            cout << strengthExerciseIndexes.size() << ". "
                 << exercises[i]->getName() << endl;
        }
    }

    if (strengthExerciseIndexes.empty()) {
        cout << "\nNo strength exercises available for one rep max calculation.\n";
        return;
    }

    int choice = readIntInRange(
        "Choose exercise: ",
        1,
        (int)strengthExerciseIndexes.size()
    );

    int realExerciseIndex = strengthExerciseIndexes[choice - 1];
    string exerciseName = exercises[realExerciseIndex]->getName();

    double weightKg = readDoubleInRange("Enter weight in kg: ", 1, 500);
    int reps = readIntInRange("Enter reps: ", 1, 30);

    OneRepMaxCalculator calculator(exerciseName, weightKg, reps);

    cout << fixed << setprecision(2);
    cout << "\n===== One Rep Max Calculator =====\n";
    cout << "Exercise: " << calculator.getExerciseName() << endl;
    cout << "Weight: " << calculator.getWeightKg() << " kg" << endl;
    cout << "Reps: " << calculator.getReps() << endl;
    cout << "Estimated 1RM: " << calculator.calculate() << " kg" << endl;
}

void calculateBodyFat(const UserProfile& user) {
    cout << "\n===== Body Fat Percentage Calculator =====\n";
    cout << "Choose calculation method:\n";
    cout << "1. Simple estimate using your profile data\n";
    cout << "2. More detailed estimate using waist, neck and hip measurements\n";

    int methodChoice = readIntInRange("Choose option: ", 1, 2);

    BodyFatCalculator* calculator = nullptr;

    if (methodChoice == 1) {
        calculator = new BodyFatCalculator(
            user.getGender(),
            user.getAge(),
            user.getHeightCm(),
            user.getWeightKg()
        );
    } else {
        double waistCm = readDoubleInRange("Enter waist in cm: ", 40, 200);
        double neckCm = readDoubleInRange("Enter neck in cm: ", 20, 70);
        double hipCm = 0;

        if (user.getGender() == "Female") {
            hipCm = readDoubleInRange("Enter hip in cm: ", 50, 200);
        }

        calculator = new BodyFatCalculator(
            user.getGender(),
            user.getHeightCm(),
            waistCm,
            neckCm,
            hipCm
        );
    }

    double result = calculator->calculate();

    cout << fixed << setprecision(2);
    cout << "\nMethod: " << calculator->getMethodName() << endl;

    if (result < 0) {
        cout << "The entered data produced an unrealistic body fat result.\n";
        cout << "Please check the measurements and try again.\n";
    } else {
        cout << "Estimated body fat: " << result << "%" << endl;
        cout << "Use this as an estimate, not as a medical measurement.\n";
    }

    delete calculator;
}

void calculateCalories(const UserProfile& user) {
    CalorieCalculator calculator(
        user.getGender(),
        user.getAge(),
        user.getHeightCm(),
        user.getWeightKg(),
        user.getActivityLevel(),
        user.getGoal()
    );

    cout << fixed << setprecision(2);
    cout << "\n===== Daily Calorie Result =====\n";
    cout << "Gender: " << user.getGender() << endl;
    cout << "Age: " << user.getAge() << endl;
    cout << "Height: " << user.getHeightCm() << " cm" << endl;
    cout << "Weight: " << user.getWeightKg() << " kg" << endl;
    cout << "Goal: " << user.getGoal() << endl;
    cout << "Activity level: " << user.getActivityLevel() << endl;
    cout << "Recommended daily calories: "
         << calculator.calculate() << " kcal" << endl;
    cout << calculator.getRecommendation() << endl;
    cout << "This is an estimate, not a medical nutrition plan.\n";
}

void showMenu(bool theoryCoursePassed) {
    cout << "\n===== Fitness Tracker =====\n";
    cout << "1. Show user profile\n";
    cout << "2. Show exercise database\n";
    cout << "3. Show personalized workout\n";
    cout << "4. Calculate one rep max\n";
    cout << "5. Calculate body fat percentage\n";
    cout << "6. Calculate daily calories\n";
    cout << "7. Generate workout plan by equipment\n";
    cout << "8. Start fitness challenge\n";
    cout << "9. Add or update personal record\n";
    cout << "10. Show personal records\n";
    cout << "11. Start mini theory course and quiz\n";

    if (theoryCoursePassed) {
        cout << "12. Build your own workout - unlocked\n";
    } else {
        cout << "12. Build your own workout - locked until theory quiz is passed\n";
    }

    cout << "13. Export progress report to file\n";
    cout << "14. Exit\n";
    cout << "Choose option: ";
}

int main() {
    UserProfile user = createUserProfile();
    vector<Exercise*> exercises = createExerciseDatabase();
    RecordManager recordManager;
    bool theoryCoursePassed = false;

    int choice;

    do {
        showMenu(theoryCoursePassed);
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "\nInvalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                user.showProfile();
                break;

            case 2:
                showExerciseDatabase(exercises);
                break;

            case 3:
                showPersonalizedWorkout(exercises, user);
                break;

            case 4:
                calculateOneRepMax(exercises);
                break;

            case 5:
                calculateBodyFat(user);
                break;

            case 6:
                calculateCalories(user);
                break;

            case 7:
                generateWorkoutPlanByEquipment(exercises);
                break;

            case 8:
                startFitnessChallenge(exercises);
                break;

            case 9:
                trackPersonalRecord(exercises, recordManager, user);
                break;

            case 10:
                recordManager.showAllRecords();
                break;

            case 11:
                if (startTheoryCourse()) {
                    theoryCoursePassed = true;
                }
                break;

            case 12:
                buildCustomWorkoutAfterTheory(exercises, theoryCoursePassed);
                break;

            case 13:
                exportProgressReport(user, recordManager);
                break;

            case 14:
                cout << "\nExiting Fitness Tracker...\n";
                break;

            default:
                cout << "\nInvalid option. Try again.\n";
                break;
        }

    } while (choice != 14);

    for (Exercise* exercise : exercises) {
        delete exercise;
    }

    return 0;
}
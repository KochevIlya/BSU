package com.example.quiz;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
TextView totalQuestionsTextView;
int score=0;
int totalQuestions=QuestionAnswer.choices.length;
TextView questionTextView;
int currentQuestionIndex=0;
String selectedAnswer = "";
Button ansA;
Button ansB;
Button ansC;
Button ansD;
Button submitBtn;
@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        totalQuestionsTextView=findViewById(R.id.TotalQuestions);
        questionTextView=findViewById(R.id.question);
        ansA=findViewById(R.id.ans_1);
        ansB=findViewById(R.id.ans_2);
        ansC=findViewById(R.id.ans_3);
        ansD=findViewById(R.id.ans_4);
        submitBtn=findViewById(R.id.submit);
        totalQuestionsTextView.setText("Total Questions : "+totalQuestions);
        ansA.setOnClickListener(this);
        ansB.setOnClickListener(this);
        ansC.setOnClickListener(this);
        ansD.setOnClickListener(this);
        submitBtn.setOnClickListener(this);
        loadNewQuestion();
    }

    @Override
    public void onClick(View v) {

        Button clickedButton=(Button) v;

        if(clickedButton.getId()==R.id.submit){
            if(selectedAnswer.equals(QuestionAnswer.correct_answers[currentQuestionIndex])) {
                score++;
            }
            currentQuestionIndex++;
            //can't load the question throw the exception
            loadNewQuestion();
        }
        else{
            selectedAnswer=clickedButton.getText().toString();
            ansA.setBackgroundColor(Color.WHITE);
            ansB.setBackgroundColor(Color.WHITE);
            ansC.setBackgroundColor(Color.WHITE);
            ansD.setBackgroundColor(Color.WHITE);
            clickedButton.setBackgroundColor(Color.BLUE);
        }
    }
    //can't open the dialogue window in the end
    void loadNewQuestion(){

        if (currentQuestionIndex==totalQuestions){
            FinishQuiz();
            return;
        }
        questionTextView.setText(QuestionAnswer.question[currentQuestionIndex]);
        ansA.setText(QuestionAnswer.choices[currentQuestionIndex][0]);
        ansB.setText(QuestionAnswer.choices[currentQuestionIndex][1]);
        ansC.setText(QuestionAnswer.choices[currentQuestionIndex][2]);
        ansD.setText(QuestionAnswer.choices[currentQuestionIndex][3]);

    }
    @SuppressLint("SuspiciousIndentation")
    void FinishQuiz(){
        String results="";
        if(score>totalQuestions*0.60){
            results="You did well";
        }
        else
        results ="You can always do better";
        new AlertDialog.Builder(this).setTitle(results).setMessage("Your score is:"+ score+"out of"+ totalQuestions)
                .setPositiveButton("Restart",(dialogueInterface,i)->restartQuiz());
    }
    void restartQuiz()
    {
        score=0;
        currentQuestionIndex=0;
        loadNewQuestion();
    }

}
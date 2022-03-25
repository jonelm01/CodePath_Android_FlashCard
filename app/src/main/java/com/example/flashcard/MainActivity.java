package com.example.flashcard;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.google.android.material.snackbar.Snackbar;

import java.util.List;

public class MainActivity extends AppCompatActivity {
    boolean isShowing=true;

    FlashcardDatabase flashcardDatabase;
    List<Flashcard> allFlashcards;
    int currentCardDisplayedIndex = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        findViewById(R.id.actButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, MainActivity2.class);
                MainActivity.this.startActivityForResult(intent, 100);
            }
        });

        findViewById(R.id.flashcard_question).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findViewById(R.id.flashcard_answers).setVisibility(View.VISIBLE);
                findViewById(R.id.flashcard_question).setVisibility(View.INVISIBLE);
            }
        });

        findViewById(R.id.flashcard_answers).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findViewById(R.id.flashcard_answers).setVisibility(View.INVISIBLE);
                findViewById(R.id.flashcard_question).setVisibility(View.VISIBLE);
            }
        });

        findViewById(R.id.answer1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findViewById(R.id.answer1).setBackgroundColor(getResources().getColor(R.color.green));
            }
        });
        findViewById(R.id.answer2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findViewById(R.id.answer2).setBackgroundColor(getResources().getColor(R.color.red));
            }
        });
        findViewById(R.id.answer3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                findViewById(R.id.answer3).setBackgroundColor(getResources().getColor(R.color.red));
            }
        });

        findViewById(R.id.nextButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(allFlashcards.size()==0)
                    return;
                currentCardDisplayedIndex++;
                if (currentCardDisplayedIndex >= allFlashcards.size()){
                    Snackbar.make(findViewById(R.id.flashcard_question),
                            "End of cards, returning to start",
                            Snackbar.LENGTH_SHORT)
                            .show();
                    currentCardDisplayedIndex=0;
                }
                allFlashcards = flashcardDatabase.getAllCards();
                Flashcard flashcard = allFlashcards.get(currentCardDisplayedIndex);
                ((TextView) findViewById(R.id.flashcard_question)).setText(flashcard.getQuestion());
                ((TextView) findViewById(R.id.flashcard_answers)).setText(flashcard.getAnswer());
            }

        });
        findViewById(R.id.toggle_vis).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (isShowing==true){
                    findViewById(R.id.answer1).setVisibility(View.INVISIBLE);
                    findViewById(R.id.answer2).setVisibility(View.INVISIBLE);
                    findViewById(R.id.answer3).setVisibility(View.INVISIBLE);
                    isShowing=false;
                }
                else if (isShowing==false){
                    findViewById(R.id.answer1).setVisibility(View.VISIBLE);
                    findViewById(R.id.answer2).setVisibility(View.VISIBLE);
                    findViewById(R.id.answer3).setVisibility(View.VISIBLE);
                    isShowing=true;

                }
            }
        });

        flashcardDatabase = new FlashcardDatabase(getApplicationContext());
        allFlashcards = flashcardDatabase.getAllCards();
        if(allFlashcards.size() >0 && allFlashcards != null ){
            ((TextView) findViewById(R.id.flashcard_question)).setText(allFlashcards.get(0).getQuestion());
            ((TextView) findViewById(R.id.flashcard_answers)).setText(allFlashcards.get(0).getAnswer());
        }

    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode==100){
            if(resultCode==RESULT_OK){
            String string1 = data.getExtras().getString("string1");
            String string2 = data.getExtras().getString("string2");
                ((TextView)findViewById(R.id.flashcard_question)).setText(string1);
                ((TextView)findViewById(R.id.flashcard_answers)).setText(string2);
                flashcardDatabase.insertCard(new Flashcard(string1, string2));
                allFlashcards = flashcardDatabase.getAllCards();
                Snackbar.make(findViewById(R.id.flashcard_question),
                        "Tap question to see answer",
                        Snackbar.LENGTH_SHORT)
                        .show();
        }}
    }


}
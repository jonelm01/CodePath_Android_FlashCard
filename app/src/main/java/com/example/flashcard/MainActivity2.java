package com.example.flashcard;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity2 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        findViewById(R.id.saveActButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //((EditText) findViewById(R.id.editTextField)).getText().toString();
                //((EditText) findViewById(R.id.editAnswerTextField)).getText().toString();
                Intent data = new Intent();
                data.putExtra("string1", ((EditText)findViewById(R.id.editTextField)).getText().toString());
                data.putExtra("string2", ((EditText) findViewById(R.id.editAnswerTextField)).getText().toString());
                setResult(RESULT_OK, data);
                finish();
                overridePendingTransition(R.anim.right_in, R.anim.left_out);

            }
        });

        findViewById(R.id.returnActButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
                overridePendingTransition(R.anim.right_in, R.anim.left_out);

            }
        });
    }
}
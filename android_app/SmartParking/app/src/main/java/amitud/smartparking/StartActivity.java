package amitud.smartparking;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import com.dropbox.sync.android.DbxAccountManager;

public class StartActivity extends AppCompatActivity {

    private DbxAccountManager mDbxAcctMgr;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mDbxAcctMgr = DbxAccountManager.getInstance(getApplicationContext(), "0yov57st6hazwn8", "kfedrhf3hbjrm9t");

        setContentView(R.layout.activity_start);
    }
}

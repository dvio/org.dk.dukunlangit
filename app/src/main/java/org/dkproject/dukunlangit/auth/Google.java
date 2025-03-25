package org.dkproject.dukunlangit.auth;

import com.tgc.sky.accounts.SystemAccountType;
import org.dkproject.dukunlangit.auth.WebLogin;


public class Google extends WebLogin {
    public Google() {
        super("Google", SystemAccountType.kSystemAccountType_Google); }
}

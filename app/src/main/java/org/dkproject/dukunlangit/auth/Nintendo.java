package org.dkproject.dukunlangit.auth;

import com.tgc.sky.accounts.SystemAccountType;

import org.dkproject.dukunlangit.auth.WebLogin;

public class Nintendo extends WebLogin {
    public Nintendo() {
        super("Nintendo", SystemAccountType.kSystemAccountType_Nintendo);
    }
}

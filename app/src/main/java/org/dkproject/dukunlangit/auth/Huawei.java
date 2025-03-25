package org.dkproject.dukunlangit.auth;

import com.tgc.sky.accounts.SystemAccountType;

import org.dkproject.dukunlangit.auth.WebLogin;

public class Huawei extends WebLogin {
    public Huawei() {
        super("Huawei", SystemAccountType.kSystemAccountType_Huawei);
    }
}

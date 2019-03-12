package com.ezored.sample.event;

public class BaseEvent {

    protected String tag;

    public boolean tagIsEqual(String tagToCompare) {
        if (tag == null) {
            return false;
        }

        return tag.equals(tagToCompare);
    }

    public String getTag() {
        return tag;
    }

    public void setTag(String tag) {
        this.tag = tag;
    }

}

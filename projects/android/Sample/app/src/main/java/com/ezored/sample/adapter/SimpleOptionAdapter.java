package com.ezored.sample.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.RecyclerView;
import com.ezored.helpers.SharedDataHelper;
import com.ezored.sample.R;
import com.ezored.sample.enums.SimpleOptionTypeEnum;
import com.ezored.sample.models.SimpleOption;

import java.util.ArrayList;

public class SimpleOptionAdapter extends RecyclerView.Adapter<SimpleOptionAdapter.ViewHolder> {

    private SimpleOptionAdapterListener listener;
    private Context context;
    private ArrayList<SimpleOption> listData;

    public SimpleOptionAdapter(Context context, ArrayList<SimpleOption> listData) {
        this.context = context;
        this.listData = listData;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(context);
        View view = inflater.inflate(R.layout.list_item_simple_option, parent, false);

        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        SimpleOption option = listData.get(position);

        if (option.getType().equals(SimpleOptionTypeEnum.SHARED_DATA)) {
            boolean demoFlag = SharedDataHelper.getDemoFlag();
            holder.tvTitle.setText(context.getString(R.string.option_shared_data, demoFlag ? "ON" : "OFF"));
        } else {
            holder.tvTitle.setText(option.getDescription(getContext()));
        }

        holder.ivIcon.setImageResource(option.getImage(getContext()));
        holder.ivIcon.setColorFilter(ContextCompat.getColor(context, R.color.list_item_icon_color));
    }

    @Override
    public int getItemCount() {
        if (listData == null) {
            return 0;
        }

        return listData.size();
    }

    public Context getContext() {
        return context;
    }

    public void setListener(SimpleOptionAdapterListener listener) {
        this.listener = listener;
    }

    public interface SimpleOptionAdapterListener {
        void onSimpleOptionItemClick(View view, int position);
    }

    public class ViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {

        private TextView tvTitle;
        private ImageView ivIcon;

        public ViewHolder(View itemView) {
            super(itemView);

            tvTitle = itemView.findViewById(R.id.tv_title);
            ivIcon = itemView.findViewById(R.id.iv_icon);

            itemView.setOnClickListener(this);
        }

        @Override
        public void onClick(View view) {
            if (listener != null) {
                listener.onSimpleOptionItemClick(view, getAdapterPosition());
            }
        }

    }

}

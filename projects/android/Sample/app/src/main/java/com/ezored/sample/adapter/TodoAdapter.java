package com.ezored.sample.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.RecyclerView;
import com.ezored.domain.Todo;
import com.ezored.sample.R;

import java.util.ArrayList;
import java.util.Locale;

public class TodoAdapter extends RecyclerView.Adapter<TodoAdapter.ViewHolder> {

    private TodoAdapterListener listener;
    private Context context;
    private ArrayList<Todo> listData;

    public TodoAdapter(Context context, ArrayList<Todo> listData) {
        this.context = context;
        this.listData = listData;
    }

    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(context);
        View view = inflater.inflate(R.layout.list_item_todo, parent, false);

        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        Todo todo = listData.get(position);

        holder.tvId.setText(String.format(Locale.getDefault(), "ID: %d", todo.getId()));
        holder.tvTitle.setText(String.format(Locale.getDefault(), "Title: %s", todo.getTitle()));
        holder.tvBody.setText(String.format(Locale.getDefault(), "Body: %s", todo.getBody()));
        holder.tvCreatedAt.setText(String.format(Locale.getDefault(), "Created at: %s", todo.getCreatedAt()));

        if (todo.getDone()) {
            holder.ivIcon.setImageResource(R.drawable.ic_item_on);
        } else {
            holder.ivIcon.setImageResource(R.drawable.ic_item_off);
        }

        holder.ivIcon.setColorFilter(ContextCompat.getColor(context, R.color.black));
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

    public void setListener(TodoAdapterListener listener) {
        this.listener = listener;
    }

    public interface TodoAdapterListener {
        void onTodoItemClick(View view, int position);
    }

    public class ViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {

        private TextView tvId;
        private TextView tvTitle;
        private TextView tvBody;
        private TextView tvCreatedAt;
        private ImageView ivIcon;

        public ViewHolder(View itemView) {
            super(itemView);

            tvId = itemView.findViewById(R.id.tv_id);
            tvTitle = itemView.findViewById(R.id.tv_title);
            tvBody = itemView.findViewById(R.id.tv_body);
            tvCreatedAt = itemView.findViewById(R.id.tv_created_at);
            ivIcon = itemView.findViewById(R.id.iv_icon);

            itemView.setOnClickListener(this);
        }

        @Override
        public void onClick(View view) {
            if (listener != null) {
                listener.onTodoItemClick(view, getAdapterPosition());
            }
        }

    }

}

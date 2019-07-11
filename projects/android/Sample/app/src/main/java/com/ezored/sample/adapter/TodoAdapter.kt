package com.ezored.sample.adapter

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.RecyclerView
import com.ezored.domain.Todo
import com.ezored.sample.R
import java.util.*

class TodoAdapter : RecyclerView.Adapter<TodoAdapter.ViewHolder> {

    private val context: Context
    private val listData: ArrayList<Todo>?
    private var listener: TodoAdapterListener? = null

    constructor(context: Context, listData: ArrayList<Todo>?) : super() {
        this.context = context
        this.listData = listData
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val inflater = LayoutInflater.from(context)
        val view = inflater.inflate(R.layout.list_item_todo, parent, false)

        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val todo = listData!![position]

        holder.tvId.text = String.format(Locale.getDefault(), "ID: %d", todo.id)
        holder.tvTitle.text = String.format(Locale.getDefault(), "Title: %s", todo.title)
        holder.tvBody.text = String.format(Locale.getDefault(), "Body: %s", todo.body)
        holder.tvCreatedAt.text = String.format(Locale.getDefault(), "Created at: %s", todo.createdAt)

        if (todo.done) {
            holder.ivIcon.setImageResource(R.drawable.ic_item_on)
        } else {
            holder.ivIcon.setImageResource(R.drawable.ic_item_off)
        }

        holder.ivIcon.setColorFilter(ContextCompat.getColor(context, R.color.black))
    }

    override fun getItemCount(): Int {
        return listData?.size ?: 0

    }

    fun setListener(listener: TodoAdapterListener) {
        this.listener = listener
    }

    interface TodoAdapterListener {
        fun onTodoItemClick(view: View, position: Int)
    }

    inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView), View.OnClickListener {

        val tvId: TextView
        val tvTitle: TextView
        val tvBody: TextView
        val tvCreatedAt: TextView
        val ivIcon: ImageView

        init {
            tvId = itemView.findViewById(R.id.tv_id)
            tvTitle = itemView.findViewById(R.id.tv_title)
            tvBody = itemView.findViewById(R.id.tv_body)
            tvCreatedAt = itemView.findViewById(R.id.tv_created_at)
            ivIcon = itemView.findViewById(R.id.iv_icon)

            itemView.setOnClickListener(this)
        }

        override fun onClick(view: View) {
            if (listener != null) {
                listener!!.onTodoItemClick(view, adapterPosition)
            }
        }

    }

}
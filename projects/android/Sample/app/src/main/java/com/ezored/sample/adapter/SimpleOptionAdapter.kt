package com.ezored.sample.adapter

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.RecyclerView
import com.ezored.helpers.SharedDataHelper
import com.ezored.sample.R
import com.ezored.sample.enums.SimpleOptionTypeEnum
import com.ezored.sample.models.SimpleOption
import java.util.*

class SimpleOptionAdapter : RecyclerView.Adapter<SimpleOptionAdapter.ViewHolder> {

    private val context: Context
    private val listData: ArrayList<SimpleOption>?
    private var listener: SimpleOptionAdapterListener? = null

    constructor(context: Context, listData: ArrayList<SimpleOption>?) : super() {
        this.context = context
        this.listData = listData
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val inflater = LayoutInflater.from(context)
        val view = inflater.inflate(R.layout.list_item_simple_option, parent, false)

        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val option = listData!![position]

        if (option.type == SimpleOptionTypeEnum.SHARED_DATA) {
            val demoFlag = SharedDataHelper.getDemoFlag()
            holder.tvTitle.text = context.getString(R.string.option_shared_data, if (demoFlag) "ON" else "OFF")
        } else {
            holder.tvTitle.text = option.getDescription(context)
        }

        holder.ivIcon.setImageResource(option.getImage(context))
        holder.ivIcon.setColorFilter(ContextCompat.getColor(context, R.color.list_item_icon_color))
    }

    override fun getItemCount(): Int {
        return listData?.size ?: 0

    }

    fun setListener(listener: SimpleOptionAdapterListener) {
        this.listener = listener
    }

    interface SimpleOptionAdapterListener {
        fun onSimpleOptionItemClick(view: View, position: Int)
    }

    inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView), View.OnClickListener {

        val tvTitle: TextView
        val ivIcon: ImageView

        init {
            tvTitle = itemView.findViewById(R.id.tv_title)
            ivIcon = itemView.findViewById(R.id.iv_icon)

            itemView.setOnClickListener(this)
        }

        override fun onClick(view: View) {
            if (listener != null) {
                listener!!.onSimpleOptionItemClick(view, adapterPosition)
            }
        }

    }

}

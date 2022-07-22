package com.example.ffmpeg5learning.adapter

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.example.ffmpeg5learning.bean.FuncItem
import com.example.ffmpeg5learning.databinding.FunctionItemBinding

class FuncAdapter : RecyclerView.Adapter<FuncAdapter.FuncHolder>() {


    var funcItemClickCb: ((index: FuncItem) -> Unit)? = null
    private var dataList: MutableList<out FuncItem> = mutableListOf()

    @SuppressLint("NotifyDataSetChanged")
    fun refreshData(list: MutableList<out FuncItem>) {
        dataList = list
        notifyDataSetChanged()
    }

    lateinit var functionItemBinding: FunctionItemBinding


    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): FuncHolder {
        functionItemBinding =
            FunctionItemBinding
                .inflate(LayoutInflater.from(parent.context), parent, false)
        return FuncHolder(functionItemBinding.root)
    }

    override fun onBindViewHolder(holder: FuncHolder, position: Int) {
        holder.bindData(dataList[position])
    }

    override fun getItemCount(): Int {
        return dataList.size
    }

    inner class FuncHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {

        fun bindData(funcItem: FuncItem) {
            functionItemBinding.card.setOnClickListener {
                funcItemClickCb?.invoke(funcItem)
                funcItem.clickItem(it.context)
            }
            functionItemBinding.funcTitle.text = funcItem.funcTitle
        }
    }
}
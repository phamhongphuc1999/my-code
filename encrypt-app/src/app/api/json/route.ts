import { globalQuery } from "@/utils/api.utils";
import { encryptText } from "@/utils/encrypt.util";
import { NextResponse } from "next/server";

export async function GET() {
    const data = await globalQuery.getJson();
    return NextResponse.json({
        message: encryptText(JSON.stringify(data), "12345678"),
    });
}
